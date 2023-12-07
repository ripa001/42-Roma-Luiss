/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.gateway.ts                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:15:07 by mmarinel          #+#    #+#             */
/*   Updated: 2023/12/02 18:27:12 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

import { WebSocketGateway, SubscribeMessage, MessageBody, WebSocketServer, OnGatewayConnection, OnGatewayDisconnect, ConnectedSocket } from '@nestjs/websockets';
import { GameService, GameSocket } from './game.service';
import { CreateGameDto } from './dto/create-game.dto';
import { UpdateGameDto } from './dto/update-game.dto';
import { PlayerDto } from './dto/player.dto';
import { Socket, Server } from 'socket.io';
import { JwtService } from '@nestjs/jwt';
import { FrameDto } from './dto/frame.dto';
import { CustomizationOptions } from './dto/customization.dto';
import { endGameDto } from './dto/endGame.dto';
import { InviteDto } from './dto/invite.dto';
import { PlayersService } from 'src/players/players.service';
import { ActiveGameDto } from './dto/activeGame.dto';

// TODO
// TODO		1.1 move maps in service
// TODO		1.2 move code in service
// TODO		1.3 make endGame a function
// TODO			and keep disconnection simple
// TODO		1.4 

const debug = false;

@WebSocketGateway({
	cors: {
		origin: process.env.FRONTEND_URL
	},
	namespace: "game"
})
export class GameGateway implements OnGatewayConnection, OnGatewayDisconnect {

	@WebSocketServer()
	private server: Server;
	private clients: Map<number, Socket>;

	constructor(
		private readonly gameService: GameService,
		private readonly jwtService: JwtService,
		private readonly pservice: PlayersService
		)
	{
		this.clients = new Map<number, Socket>();
	}

	async handleConnection(client: Socket, ...args: any[]) {
		// validating user
		const user = await this.jwtService.verifyAsync(client.handshake.auth.token, {
			secret: process.env.JWT_SECRET
		});

		// setting user socket
		if (!this.clients.has(Number(user.sub)))
			this.clients.set(Number(user.sub), client);
		
		if (debug) console.log(`| GATEWAY GAME | socket: ${client.id}, userID: ${Number(user.sub)}, connected`);
		if (debug) console.log(`| GATEWAY GAME | current queue : ${this.gameService.getQueue().size} `);
	}

	async handleDisconnect(client: any) {
		if (debug) console.log(`| GATEWAY GAME | ${client.id} disconnected`);
		
		let id: number = -1;
		
		// deleting among the list of clients
		for (let [userID, csock] of this.clients) {
			if (client.id == csock.id) {
				id = userID;
				break ;
			}
		}
		
		if (-1 != id) {
			if (debug) console.log(`GAME GATEWAY | disconnecting user ${id}`);
			if (this.pservice.isLoggedIn(id)) {
				this.pservice.changeConnection(id, {
					playing: false
				});
				this.broadcastPlayerStatus(id);
			}
			this.clients.delete(id);
		}
		
		this.gameService.leaveGame(client, this.server);
	}

	async broadcastPlayerStatus(
		userID: number
	)
	{
		console.log(`GAME GATEWAY | broadcastPlayerStatus`);
		
		const newStatus = this.pservice.getConnection(userID);
		const friends = await this.pservice.getAllFriends(userID, false);
		
		console.log(`iterating over friends`);
		for (const friend of friends)
		{
			console.log('found friend');
			const friend_client = this.clients.get(friend.id);
			if (undefined == friend_client)
				continue ;
			console.log('found friend active client');
			this.server.to(friend_client.id).emit("friendStatusUpdate", {
				userID,
				status : newStatus
			} as { userID : number, status : 'offline' | 'online' | 'playing' });
		}
	}

	@SubscribeMessage('getActiveGames')
	getActiveGames(
		@ConnectedSocket() client: Socket
	) {
		if (debug) console.log(`GAME | getActiveGames`);

		const activeGames = this.gameService.getActiveGames();

		this.server.to(client.id).emit('getActiveGames',activeGames);
	}

	// joining game through invite
	// from sender to receiver
	@SubscribeMessage('sendInvite')
	sendInvite(
		@MessageBody('invite') invite: InviteDto
	){
		if (debug) console.log(`| GATEWAY GAME | 'sendInvite'`);
		if (debug) console.log(invite)

		// handle valid request
		if (invite && invite.hostID ){
			let senderSocket = this.clients.get(invite.hostID);
			if (senderSocket && invite.guestID){
				let recipientSocket = this.clients.get(invite.guestID);
				if (recipientSocket){
					if ((false === this.gameService.isUserBusy(invite.hostID))
					&& (false === this.gameService.isUserBusy(invite.guestID))){
						if (debug) console.log(`recipient socket : ${recipientSocket.id}`)
						this.server.to(`${recipientSocket.id}`).emit("newInvite", invite);
						if (debug) console.log(`| GATEWAY GAME | 'sendInvite' | emit : 'newInvite'`);
						return
					}
				}
			}
			// handle empty input | host or guest left | handle requestor or recipient busy
			if (senderSocket){
				this.server.to(`${senderSocket.id}`).emit("rejectedInvite", invite);
				if (debug) console.log(`| GATEWAY GAME | 'rejectInvite' | emit : 'rejectedInvite'`);			
			}
		}
	}

	@SubscribeMessage('cancelInvite')
	cancelInvite(@MessageBody('invite') invite: InviteDto )
	{
		if (debug) console.log(`| GATEWAY GAME | 'cancelInvite'`);
		if (debug) console.log(invite)

		if (!invite?.hostID || !invite?.guestID)
			return

			let recipientSocket = this.clients.get(invite?.guestID);

			if (debug) console.log(`recipient socket : ${recipientSocket?.id}`)

		if (recipientSocket)
		{
			this.server.to(`${recipientSocket.id}`).emit("deleteInvite", invite);
			if (debug) console.log(`| GATEWAY GAME | 'cancelInvite' | emit : 'deleteInvite'`);
		}
	}
	// from receiver to sender
	@SubscribeMessage('rejectInvite')
	rejectInvite(@MessageBody('invite') invite: InviteDto )
	{
		if (debug) console.log(`| GATEWAY GAME | 'rejectInvite'`);
		if (debug) console.log(invite)

		if (!invite?.hostID || !invite?.guestID)
			return

		let requestorSocket = this.clients.get(invite?.hostID);
		if (debug) console.log(`recipient requestorSocket : ${requestorSocket.id}`)

		if (requestorSocket)
		{
			this.server.to(`${requestorSocket.id}`).emit("rejectedInvite", invite);
			if (debug) console.log(`| GATEWAY GAME | 'rejectInvite' | emit : 'rejectedInvite'`);
		}
	}
	@SubscribeMessage('acceptInvite')
	acceptInvite(@MessageBody('invite') invite: InviteDto ) {
		if (debug) console.log(`| GATEWAY GAME | 'acceptInvite'`);
		if (debug) console.log(invite)

		if (!invite?.hostID || !invite?.guestID)
			return

		const host_socket = this.clients.get(invite?.hostID);
		const guest_socket = this.clients.get(invite?.guestID);
		if (debug) console.log(`host_socket : ${host_socket?.id}`)
		if (debug) console.log(`guest_socket : ${guest_socket?.id}`)
		
		// Create game instance
		let roomId = this.gameService.matchPlayers(
			invite?.guestID, invite?.hostID,
			host_socket, guest_socket
		);
		
		// start game
		this.server.to(roomId).emit("newGame", {
			hostID: invite?.hostID,
			guestID: invite?.guestID,
			watcher: false
		} as CreateGameDto);
		if (debug) console.log(`| GATEWAY GAME | 'acceptInvite' | emit : 'newGame'`);
	}

	// joining game through matchmaking
	@SubscribeMessage('matchMaking')
	async matchMaking(
		@MessageBody('userID') userID: number,
		@ConnectedSocket() userSocket: Socket
	)
	{
		if (debug) console.log(`| GATEWAY GAME | 'matchMaking' |`);
		if (!userID || !userSocket)
			return
			
		if (true === this.gameService.isUserBusy(userID)){
			this.server.to(userSocket.id).emit('alert', {message : 'You are already busy'});
			return
		}

		if (debug) console.log(`| GATEWAY GAME | current queue : ${this.gameService.getQueue().size} `);
		if (debug) console.log(`| GATEWAY GAME | current live games : ${this.gameService.getGameInstances().size} `);
		let matched: boolean = false;
		let roomId: string;



		for (let [hostID, hostSocket] of this.gameService.getQueue()) {
			if (await this.gameService.playerMatch(hostID, userID))
			{
				// create match
				roomId = this.gameService.matchPlayers(userID, hostID, hostSocket, userSocket);

				// emit event in the room
				this.server.to(roomId).emit('newGame', {
					hostID,
					guestID: userID,
					watcher: false
				} as CreateGameDto);
				if (debug) console.log(`| GATEWAY GAME | 'matchMaking' | emit : 'newGame'`);

				// exit loop
				matched = true;
				break ;
			}
		}

		// add to queue if could not find match
		if (false == matched)
		{
			if (debug) console.log(`| GATEWAY GAME | 'matchMaking' | not matched `);
			this.gameService.getQueue().set(userID, userSocket);
		}
		if (debug) console.log(`| GATEWAY GAME | current queue : ${this.gameService.getQueue().size} `);
		if (debug) console.log(`| GATEWAY GAME | current live games : ${this.gameService.getGameInstances().size / 2} `);
	}

	@SubscribeMessage("cancelMatchMaking")
	cancelMatchMaking(
		@MessageBody('userID') userID: number,
		@ConnectedSocket() socket: Socket
	) {
		if (!userID)
			return 
		if (debug) console.log(`| GATEWAY GAME | 'cancelMatchMaking'`);

		// if(this.gameService.removeFromQueue(userID))
		// 	this.server.to(socket.id).emit("cancelMatchMaking");

		this.gameService.removeFromQueue(userID);
	}

	// customization
	@SubscribeMessage('sendCustomizationOptions')
	sendCustOptions(
		@MessageBody('customization') customization: CustomizationOptions,
		@MessageBody('gameInfo') gameInfo: CreateGameDto,
		@MessageBody('userID') userID: number,
	) {
		if (!userID || !gameInfo || !customization)
			return
		if (debug) console.log(`| GATEWAY GAME | 'sendCustomizationOptions'`);
		if (debug) console.log(`${customization.ball_color}`);
		if (debug) console.log(`${customization.paddle_color}`);
		if (debug) console.log(`${customization.pitch_color}`);

		const resp = this.gameService.sendCustomizationOptions(
			userID,
			gameInfo,
			customization
		);

		if (resp)
		{
			// sending start game to participants
			this.server.to(resp.roomId).emit('startGame',
				resp.final_customization
			);
			
			// Sending updated list of active games to all
			this.gameService.calculateActiveGames();
			this.server.emit('getActiveGames', this.gameService.getActiveGames());
			
			// changing status of host and guest to 'Playing'
			this.pservice.changeConnection(gameInfo.hostID, {
				playing: true
			});
			this.broadcastPlayerStatus(gameInfo.hostID);

			this.pservice.changeConnection(gameInfo.guestID, {
				playing: true
			});
			this.broadcastPlayerStatus(gameInfo.guestID);

			
			if (debug) console.log(`| GATEWAY GAME | 'sendCustOptions' | emit : 'startGame'`);
		}
	}

	//joining game for livestream
	// SISTEMARE LE CHIAMATE CON UNA SOLA NUOVA PER IL STREAMING
	@SubscribeMessage('joinGame')
	joinGame(
		@MessageBody('userID') userID: number,
		@MessageBody('playerID') playerID: number,
		@ConnectedSocket() client: Socket
	) {
		if (debug) console.log(`| GATEWAY GAME | 'joinGame'`);
		if (!userID || !playerID || !client)
			return

		if (true === this.gameService.isUserBusy(userID)){
			this.server.to(client.id).emit('alert', {message : 'You are already busy'});
			return
		}

		// fetching the room where playerID is playing
		const game = this.gameService.joinGame(userID, playerID, client);

		if (game)
		{
			// handleNewStream
			const gameInfo = {
				hostID: game.hostID,
				guestID: game.guestID,
				watcher: true
			} as CreateGameDto

			const final_customizations = {
				customization : game.customization.customization,
				pitch_color: game.customization.pitch_color,
				paddle_color: game.customization.paddle_color,
				ball_color: game.customization.ball_color,
			} as CustomizationOptions

			this.server.to(`${client.id}`).emit("newStream", gameInfo, final_customizations);
			console.log(`| GATEWAY GAME | 'joinGame' | emit : 'newStream'`);
			console.log(gameInfo, final_customizations)

			// joining the room (which start sending 'newFrame' events)
			client.join(game.roomId);			
		}
	}

	@SubscribeMessage('newFrame')
	async getNewFrame(
		@MessageBody('frame') frame: FrameDto,
		@MessageBody('userID') userID: number
	)
	{
		if (!userID || !frame)
			return
		// if (debug) console.log(`| GATEWAY GAME | 'newFrame'`);
		
		const	finished = (
			this.gameService.getGameInstances().get(frame.hostID)?.finished ||
			this.gameService.getGameInstances().get(frame.guestID)?.finished
		);
		const	roomId: string = this.gameService.getGameInstances().get(userID).roomId;
		const	currentFrame: FrameDto = this.gameService.getFrames().get(roomId);
		const	hostWin: boolean = (10 == frame?.data?.host?.score);
		const	guestWin: boolean = (10 == frame?.data?.guest?.score);
		const	hostScore: number = (frame?.data?.host?.score);
		const	guestScore: number = (frame?.data?.guest?.score);

		if (frame.seq >= currentFrame.seq)
		{
			// check end of game
			if (hostWin || guestWin)
			{
				// emit last frame
				this.server.to(roomId).emit("newFrame", frame);
				if (debug) console.log(`| GATEWAY GAME | 'getNewFrame' | emit : 'newFrame' | last frame`);

				this.server.to(roomId).emit("endGame", {
					hostWin,
					guestWin,
					hostScore,
					guestScore
				} as endGameDto);
				if (debug) console.log(`| GATEWAY GAME | 'getNewFrame' | emit : 'endGame'`);

				if (false === finished) {
					this.gameService.getGameInstances().get(frame.guestID).finished = true;
					this.gameService.getGameInstances().get(frame.hostID).finished = true;
					await this.gameService.setGameasFinished(frame);
				}
				// await this.gameService.updateAchievements(frame, userID);
			}

			// send next frame
			else
			{
				this.server.to(roomId).emit("newFrame", frame);
				// if (debug) console.log(`| GATEWAY GAME | 'getNewFrame' | emit : 'newFrame'`);
			}
			
			this.gameService.getFrames().set(roomId, frame);
		}
	}

	@SubscribeMessage("leaveGame")
	leaveGame(
		@MessageBody('userID') userID: number,
		@ConnectedSocket() socket: Socket
	) {
		if (!userID || !socket)
			return

			if (debug) console.log(`| GATEWAY GAME | 'leaveGame' | ${userID} `);
		
		const game = this.gameService.getGameInstances().get(userID);
		// leaveGame gets called two times with current flow
		const shutdownRoom = game && (game.hostID == userID || game.guestID == userID);

		// deleting game instance of player
		this.gameService.leaveGame(socket, this.server);
		this.broadcastPlayerStatus(userID);

		//TODO maybe add the active games as a data of class so that a game is valid
		//TODO only if it is there
		//! IMPORTANT use this check in 'joinGame' event as a user cannot join
		//! a game that has ended just right now
		//! (meaning, the opponent left, but not the user whose profile you are viewing)
		// send new active game list if one of host and guest left game
		if (shutdownRoom) {
			this.gameService.calculateActiveGames();
			this.server.emit('getActiveGames', this.gameService.getActiveGames());
		}

		for (let [userID, uSock] of this.clients) {
			if (debug) console.log(`found client`);
			if (debug) console.log(`userID: ${userID}; socket.id: ${uSock.id}`);
		}
	}

}
