import { WebSocketGateway, SubscribeMessage, MessageBody, ConnectedSocket, WebSocketServer, OnGatewayConnection, OnGatewayDisconnect } from '@nestjs/websockets';
import { FrienshipsService } from './frienships.service';
import { CreateFrienshipDto } from './dto/create-frienship.dto';
import { UpdateFrienshipDto } from './dto/update-frienship.dto';
import { Socket, Server } from 'socket.io';
import { Player } from '@prisma/client';
import { JwtService } from '@nestjs/jwt';
import { Public } from 'src/auth/decorators/auth.public.decorator';


const debug = false;

@WebSocketGateway({
	cors: {
		origin: process.env.FRONTEND_URL,
	},
})
export class FrienshipsGateway implements OnGatewayConnection, OnGatewayDisconnect {

	@WebSocketServer()
	private server: Server;
	/**
	 * key: userID
	 * value: connected Socket
	 */
	private clients: Map<number, Socket>;

	constructor(
		private readonly frienshipsService: FrienshipsService,
		private readonly jwtService: JwtService
	) {
		this.clients = new Map<number, Socket>();
	}

	//TODO add JWT guard -- && understand how to reuse the jwt guard and check wether we are on http or websockets
	@Public()
	async handleConnection(client: Socket, ...args: any[]) {
		const user = await this.jwtService.verifyAsync(client.handshake.auth.token, {
			secret: process.env.JWT_SECRET
		});
		
		if (debug) console.log(`socket: ${client.id}, userID: ${Number(user.sub)}, connected`)
		// https://socket.io/docs/v4/client-options/#auth
		console.log(`friendships gateway: ${client.id} connected, exist: ${this.clients.has(Number(user.sub))}`);
		if (!this.clients.has(Number(user.sub)))
			this.clients.set(Number(user.sub), client);
		else{
			await new Promise(r => setTimeout(r, 500));
			this.server.to(`${client.id}`).emit('already-connected')}
	}

	@Public()
	async handleDisconnect(socket: Socket) {
		if (debug) console.log(`friendships gateway: ${socket.id} disconnected`);

		let key: number = -1;
		for (let [userID, csock] of this.clients) {
			if (socket.id == csock.id) {
				key = userID;
				break ;
			}
		}

		if (-1 != key) {
			if (debug) console.log(`friendships gateway: user ${key} socket removed`);
			this.clients.delete(key);
		}
	}
	
	@Public()
	@SubscribeMessage('createFrienshipRequest')
	async createFrienshipRequest(
		@MessageBody('id') userID: number,
		@MessageBody('recipientID') recipientID: number,
		@ConnectedSocket() socket: Socket
	) {
		if (debug) console.log(`GATEWAY | createFrienshipRequest`);
		try {
			//TODO add jwt service to check if id user that sent the request matches either requestor or recipient
			//TODO otherwise, anyone connected can act upon anyone friendships
			// if (client.handshake.auth)
			const requestor = await this.frienshipsService.createFrienshipRequest(userID, recipientID);

			let recipientSocket = this.clients.get(recipientID);
			if (undefined != recipientSocket) {
				// https://socket.io/docs/v3/rooms/#default-room
				this.server.to(`${recipientSocket.id}`).emit('new-friendship-request', {
					requestorID: requestor.requestorID,
					requestorUsername: requestor.requestorUsername,
					requestorAvatar: requestor.requestorAvatar,
					recipientID: recipientID
				})
			}
			this.server.to(`${socket.id}`).emit('new-friendship-request', {
				requestorID: requestor.requestorID,
				requestorUsername: requestor.requestorUsername,
				requestorAvatar: requestor.requestorAvatar,
				recipientID: recipientID
			})
		}
		catch(error) {
			const msg: string = `new-friendship-request: ${error.toString()}`;

			this.server.to(`${this.clients.get(Number(userID)).id}`).emit('frienship-error', {
				msg: msg,
				requestorID: userID,
				recipientID: recipientID,
			})
		}
	}

	@Public()
	@SubscribeMessage('findAllFrienshipRequests')
	async findAllFrienshipRequests(
			@MessageBody('id') userID: number,
			@ConnectedSocket() requestorSocket: Socket
	) {
		try {
			//TODO add jwt service to check if id user that sent the request matches either requestor or recipient
			//TODO otherwise, anyone connected can act upon anyone friendships
			// if (client.handshake.auth)
			const friendshipRequests = await this.frienshipsService.findAllFrienshipRequests(userID);

			this.server.to(`${requestorSocket.id}`).emit('friendship-requests', {
				requests: friendshipRequests
			});
		}
		catch(error) {
			const msg: string = `friendship-requests: ${error.toString()}`;

			this.server.to(`${requestorSocket.id}`).emit('frienship-error', {
				msg: msg,
				requestorID: userID,
				recipientID: NaN
			});
		}
	}

	/**
	 * a friendship must either be pending or "are_friends" is true
	 * if any of the user is blacklisted, the are_friends fielf must be false and pending must be false,
	 * when a friendship is rejected, the record is removed
	 * A record cannot be removed if any of the users is blacklisted
	 * 
	 * All these rules must be written as constraints in postgre (maybe not the last rule)
	 * Therefore, this function will automatically fail if any of the rules are violated.
	 */
	//TODO add constraints in db for frienship fields (when a user is blacklisted pending cannot be true, when pending is true friend cannot be, etc.)
	

	/**
	 * When a user blocked you, you cannot see its profile.
	 * When you blocked a user, you CAN see its profile and click a button to unblock it.
	 * When either of the two users are blocked by the other, friendship request cannot be sent, you have to unblock it first
	 * for all other rules, see the updateFriendship handler
	 * 
	 * @param userID 
	 * @param friendID 
	 * @param client 
	 */
	@Public()
	@SubscribeMessage('ToggleBlockUser')
	async toggleBlockUser(
		@MessageBody('userID') userID: number,
		@MessageBody('friendID') friendID: number,
		@MessageBody('block') block: boolean,
		@ConnectedSocket() client: Socket
	)
	{
		let [requestorID, recipientID] = await this.frienshipsService.getFriendship(userID, friendID);

		if (debug) console.log(`DEBUG| ToggleBlockUser: userID: ${userID}; friendID: ${friendID}; block: ${block}; requestorID: ${requestorID}; recipientID: ${recipientID}`);
		try {
			[requestorID, recipientID] = await this.frienshipsService.toggleBlockUser(userID, friendID, requestorID, recipientID, block);

			if (debug) console.log(`DEBUG | after prisma: requestorID: ${requestorID}; recipientID: ${recipientID}; typeof requestorID: ${typeof requestorID}; typeof recipientID: ${typeof recipientID}`);
			let requestorSocket = this.clients.get(requestorID);
			if (undefined != requestorSocket) {
				if (debug) console.log(`DEBUG | requestor not undefined`);
				this.server
					.to(requestorSocket.id)
					.emit('toggle-block-user', {
						requestorID: requestorID,
						recipientID: recipientID,
						requestor_blacklisted: userID == recipientID ? block : undefined,
						recipient_blacklisted: userID == requestorID ? block : undefined,
					})
			}
			let recipientSocket = this.clients.get(recipientID);
			if (undefined != recipientSocket) {
				if (debug) console.log(`DEBUG | requestor not undefined`);
				this.server
					.to(recipientSocket.id)
					.emit('toggle-block-user', {
						requestorID: requestorID,
						recipientID: recipientID,
						requestor_blacklisted:  userID == recipientID ? block : undefined,
						recipient_blacklisted:  userID == requestorID ? block : undefined,
					})
			}
		}
		catch (err) {
			const msg = `blockUser: ${err.toString()}`;

			this.server
				.to(`${this.clients.get(userID).id}`)
				.emit('friendship-error', {
					msg: msg,
					requestorID: requestorID,
					recipientID: recipientID
				});
		}
	}

	@Public()
	@SubscribeMessage('acceptFriendship')
	async acceptFriendship(
		@MessageBody('requestorID') requestorID: number,
		@MessageBody('recipientID') recipientID: number,
		@ConnectedSocket() client: Socket
	)
	{
		const user = await this.jwtService.verifyAsync(client.handshake.auth.token, {
			secret: process.env.JWT_SECRET
		});
		const userID = Number(user.sub);

		try {
			if (userID != recipientID)
				throw Error('only recipient can accept friendship request');
			await this.frienshipsService.acceptFriendshipRequest(requestorID, recipientID);

			let requestorSocket = this.clients.get(requestorID);
			if (undefined != requestorSocket) {
				this.server
					.to(requestorSocket.id)
					.emit('accept-friendship', {
						requestorID,
						recipientID,
					})
			}
			let recipientSocket = this.clients.get(recipientID);
			if (undefined != recipientSocket) {
				this.server
					.to(recipientSocket.id)
					.emit('accept-friendship', {
						requestorID,
						recipientID,
					})
			}
		}
		catch (err) {
			const msg = `acceptFriendship: ${err.toString()}`;

			this.server
				.to(`${this.clients.get(userID).id}`)
				.emit('friendship-error', {
					msg: msg,
					requestorID: requestorID,
					recipientID: recipientID
				});
		}
	}

	@Public()
	@SubscribeMessage('rejectFrienship')
	async deleteFriendship(
		@MessageBody('userID') userID: number,
		@MessageBody('friendID') friendID: number,
		@ConnectedSocket() client: Socket
	)
	{
		console.log('|||||||||||||||||||Freindship gateway  | rejectFrienship')
		console.log(userID)
		console.log(friendID)
		
		let [requestorID, recipientID] = await this.frienshipsService.getFriendship(userID, friendID);

		try {
			//TODO add jwt service to check if id user that sent the request matches either requestor or recipient
			//TODO otherwise, anyone connected can act upon anyone friendships
			// if (client.handshake.auth)
			await this.frienshipsService.deleteFrienshipRequest(requestorID, recipientID);

			// console.log(`GATEWAY | friendships | removing friendship requestorID:${requestorID}, recipientID:${recipientID}`);
			let recipientSocket = this.clients.get(recipientID);
			if (undefined != recipientSocket) {
				// console.log(`recipientSocket found...emitting`);
				this.server
					.to(`${recipientSocket.id}`)
					.emit('reject-friendship-request', {
						requestorID,
						recipientID
					})
			}
			let requestorSocket = this.clients.get(requestorID);
			if (undefined != requestorSocket) {
				// console.log(`requestorSocket found...emitting`);
				this.server
					.to(`${requestorSocket.id}`)
					.emit('reject-friendship-request', {
						requestorID,
						recipientID
					})
			}
		}
		catch(err) {
			// console.log(`GATEWAY | friendships | error`);
			const msg = `rejectFrienship: ${err.toString()}`;

			this.server
				.to(`${this.clients.get(userID).id}`)
				.emit('friendship-error', {
					msg: msg,
					requestorID: requestorID,
					recipientID: recipientID
				});
		}
	}
}
