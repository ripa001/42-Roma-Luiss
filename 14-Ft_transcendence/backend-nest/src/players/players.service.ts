import { Injectable } from '@nestjs/common';
import { CreatePlayerDto } from './dto/create-player.dto';
import { UpdatePlayerDto } from './dto/update-player.dto';
import { PrismaService } from 'src/prisma/prisma.service';
import { BeFriends, Player } from '@prisma/client';

export class Connection {
	playing: boolean;
}

const debug = false;

@Injectable()
export class PlayersService {
	private connections: Map<number, Connection>;

	constructor(private readonly prisma: PrismaService) {
		if (debug) console.log('\x1b[36m%s\x1b[0m', '| constructor PlayersService');
		this.connections = new Map<number, Connection>();
	}

	addConnection(userID: number) {
		this.connections.set(userID, { playing: false });

		if (debug) console.log('\x1b[36m%s\x1b[0m', '| addConnection');
		if (debug) console.log(`| user ${userID} is :
					${this.connections.has(userID) === false ? 'offline'
					: this.connections.get(userID).playing === true ? 'playing' : 'online'}`);

					if (debug) console.log('Printing connections:');
		for (const [playerId, connection] of this.connections.entries()) {
			if (debug) console.log(`Player ID: ${playerId}, Playing: ${connection.playing}`);
		}

	}

	removeConnection(userID: number) {

		// removing the connections,
		// effectively logging out the player
		this.connections.delete(userID);

		if (debug) console.log('\x1b[36m%s\x1b[0m', '| removeConnection');
		if (debug) console.log(`| user ${userID} is :
					${this.connections.has(userID) === false ? 'offline'
					: this.connections.get(userID).playing === true ? 'playing' : 'online'}`);

		if (debug) console.log('Printing connections:');
		for (const [playerId, connection] of this.connections.entries()) {
			if (debug) console.log(`Player ID: ${playerId}, Playing: ${connection.playing}`);
			}

	}

	changeConnection(userID: number, connection: Connection)
	{
		if (debug) console.log('\x1b[36m%s\x1b[0m', '| changeConnection');
		if (debug) console.log(`| user ${userID} was :
					${this.connections.has(userID) === false ? 'offline'
					: this.connections.get(userID).playing === true ? 'playing' : 'online'}`);

		this.connections.set(userID, connection);

		if (debug) console.log(`| user ${userID} is :
					${this.connections.has(userID) === false ? 'offline'
					: this.connections.get(userID).playing === true ? 'playing' : 'online'}`);

					if (debug) console.log('Printing connections:');
		for (const [playerId, connection] of this.connections.entries()) {
			if (debug) console.log(`Player ID: ${playerId}, Playing: ${connection.playing}`);
			}
	}

	getConnection(userID: number) : 'offline' | 'online' | 'playing'
	{
	// 	const status : 'offline' | 'online' | 'playing' = 	this.connections.has(userID) ? 
	// 														(this.connections.get(userID).playing === true ? 'playing' : 'online')
	// 														:'offline'

		// if (debug) console.log('\x1b[36m%s\x1b[0m', `| getConnection : ${status}`);
		// if (debug) console.log('Printing connections:');
		// for (const [playerId, connection] of this.connections.entries()) {
		// 	if (debug) console.log(`Player ID: ${playerId}, Playing: ${connection.playing}`);
		//   }
		// return status
		return (
				this.connections.has(userID) ? 
				(this.connections.get(userID).playing === true ? 'playing' : 'online')
				:'offline'
			)
	}


	isLoggedIn(userID: number): boolean {
		return this.connections.has(userID);
	}

	// async downloadFile(url: path)

	async create(createPlayerDto: CreatePlayerDto): Promise<Player> {
		if (debug) console.log('DEBUG | Players.Service | create() : called');


		return await this.prisma.player.upsert({
			where: {
				id: createPlayerDto.id
			},
			create: {
				id: createPlayerDto.id,
				username: createPlayerDto.username,
				avatar: createPlayerDto.avatar,
				firstName: createPlayerDto.firstName,
				lastName: createPlayerDto.lastName,
				profileIntra: createPlayerDto.profileIntra,
			},
			update: {}
		});
	}

	async getLeaderboard()
	{
		let players = (
			await this.prisma.player.findMany({
				select: {
					id: true,
					username: true,
					avatar: true,
					ladder_lvl: true,
					wins: true,
					losses: true
				},
				orderBy: {ladder_lvl: 'desc'}
			})
		);

		for (let player of players)
		{
			player.avatar = `/players/avatar/${player.id}`;
		}

		return (players);
	}

	async setProfileAsComplete(userID: number) {
		await this.prisma.player.update({
			where: {
				id: userID
			},
			data: {
				profile_completed: true,
			}
		});
		//* inserting only if not already present
		await this.prisma.achieved.upsert({
			where: {
				playerID_achievementName: {
					playerID: userID,
					achievementName: 'Your Catventure begins here!',
				}
			},
			create: {
				playerID: userID,
				achievementName: 'Your Catventure begins here!',
				date_of_issue: new Date(),
			},
			update: {}
		})
	}

	async findAll(): Promise<Player[]> {
		const players = await this.prisma.player.findMany();

		for (let player of players) {
			player = {
				...player,
				...this.connections.get(player.id),
			};
		}
		return players;
	}

	async findOne(id: number): Promise<Player & Connection> {
		const player = {
			...(await this.prisma.player.findUnique({
				where: { id },
			})),
			...this.connections.get(id),
		};
		return JSON.stringify(player) == '{}' ? null : player;
	}

	async update(id: number, updatePlayerDto: UpdatePlayerDto): Promise<Player> {
		if (debug) console.log(`pservice update`);
		if (debug) console.log(updatePlayerDto);

		return await this.prisma.player.update({
			where: { id },
			data: updatePlayerDto,
		});
	}

	async remove(id: number): Promise<Player> {
		try {
			return await this.prisma.player.delete({
				where: { id },
			});
		} catch (error: any) {
			return null;
		}
	}


	async getAllPlayers(): Promise<Player[]> {
		if (debug) console.log(`DEBUG | Players.Service | getAllPlayers `);
		const players: Player[] = await this.prisma.player.findMany();
		const playerIds: number[] = players.map(player => player.id);
		if (debug) console.log(`DEBUG | Players.Service | getAllPlayers | players : ` + playerIds);
		return players
	}

	async getAllPublicUsers(userID: number): Promise<Player[]> {
		if (debug) console.log(`DEBUG | Players.Service | getAllPublicUsers | userID: ${userID}`);
		const players = await this.getAllPlayers();
		const friends = await this.getAllFriends(userID, true);
		const blocked = await this.getAllBlockedUsers(userID);

		const isKnownId = (userId : number, anyId : number) => userId == anyId;

		const publicUsers: Player[] = players.filter(player => {
			return !friends.some(friend => isKnownId(friend.id, player.id)) &&
				   !blocked.some(blockedUser => isKnownId(blockedUser.id, player.id)) &&
				   !isKnownId(userID, player.id);
		});
		const publicUsersIds: number[] = publicUsers.map(publicUser => publicUser.id);
		if (debug) console.log(`DEBUG | Players.Service | getAllPublicUsers | publicUsers : ` + publicUsersIds);

		publicUsers.forEach(
			(user) => {
				user.avatar = `players/avatar/${user.id}`;
			}
		);
		return publicUsers
	}

	async getAllPendingUsers(userID: number): Promise<Player[]> {
		if (debug) console.log(`DEBUG | Players.Service | getAllPublicUsers | userID: ${userID}`);
		const allfriends = await this.getAllFriends(userID, true);
		const myfriends = await this.getAllFriends(userID, false);

		const isKnownId = (userId : number, anyId : number) => userId == anyId;

		const pendingUsers: Player[] = allfriends.filter(player => {
			return !myfriends.some(friend => isKnownId(friend.id, player.id))
		});
		// const pendingUsersIds: number[] = pendingUsers.map(publicUser => publicUser.id);
		// if (debug) console.log(`DEBUG | Players.Service | getAllPendingUsers | pendingUsers : ` + pendingUsersIds);

		pendingUsers.forEach(
			(user) => {
				user.avatar = `players/avatar/${user.id}`;
			}
		);
		return pendingUsers
	}	

	async getAllBlockedUsers(userID: number): Promise<Player[]> {
		const asRequestorIDs = await this.prisma.beFriends.findMany({
			where: {
				requestorID: userID,
				AND: [{requestor_blacklisted: false}, {recipient_blacklisted: true}]
			},
			select: {
				recipientID: true
			}
		});
		const asRecipientIDs = await this.prisma.beFriends.findMany({
			where: {
				recipientID: userID,
				AND: [{requestor_blacklisted: true}, {recipient_blacklisted: false}]
			},
			select: {
				requestorID: true
			}
		});

		let ids: number[] = [];
		for (const id of asRequestorIDs)
			ids.push(id.recipientID);
		for (const id of asRecipientIDs)
			ids.push(id.requestorID);
		let blockedUsers: Player[] = [];
		for (const id of ids) {
			const blockedUser = await this.findOne(id);
			blockedUser.avatar = `/players/avatar/${blockedUser.id}`
			blockedUsers.push(blockedUser);
		}

		return (blockedUsers);
	}

	async getOneFriend(userID: number, friendID: number): Promise<BeFriends> {

		return (
			await this.prisma.beFriends.findUnique({
				where: {
					requestorID_recipientID: {requestorID: userID, recipientID: friendID}
				}
			})
			||
			await this.prisma.beFriends.findUnique({
				where: {
					requestorID_recipientID: {requestorID: friendID, recipientID: userID}
				}
			})
		);
	}

	async getAllFriends(userID: number, includePending: boolean): Promise<(Player & Connection)[]> {
		if (debug) console.log(`DEBUG | Players.Service | getAllFriends | userID: ${userID}`);

		// taking all friends
		const friendsAsRequestorIDs = await this.prisma.beFriends.findMany({
			where: {
				requestorID: userID,
				OR: [
					{are_friends: true},
					{...(includePending && {pending_friendship: true})}
				]
			},
			select: {
				recipientID: true,
			},
		});
		const friendsAsRecipientIDs = await this.prisma.beFriends.findMany({
			where: {
				recipientID: userID,
				OR: [
					{are_friends: true},
					{...(includePending && {pending_friendship: true})}
				]
			},
			select: {
				requestorID: true,
			},
		});

		// taking just the IDs
		const friendsIDs: number[] = [];
		for (const friend of friendsAsRequestorIDs) {
			friendsIDs.push(friend.recipientID);
		}
		for (const friend of friendsAsRecipientIDs) {
			friendsIDs.push(friend.requestorID);
		}

		if (debug) console.log(`DEBUG | Players.Service | getAllFriends | friendsIDs: ${friendsIDs}`);
		
		// taking the whole user info
		const friends = [];
		for (const friendID of friendsIDs) {
			// friends.push(await this.findOne(friendID));
			const friend = await this.findOne(friendID);
			friend.avatar = `/players/avatar/${friendID}`;
			friends.push(friend);
		}

		return friends;
	}

	// TODO make achievementName unique

	async getAllAchievements(userID: number): Promise<(Player & Connection)[]> {
		if (debug) console.log(`DEBUG | Players.Service | getAllAchievements | userID: ${userID}`);
		const achievementNames = await this.prisma.achieved.findMany({
			where: {
				playerID: userID,
			},
			select: {
				achievementName: true,
			},
		});

        if (debug) console.log(`DEBUG | Players.Service | getAllAchievements | achievementNames: ${achievementNames}`);
		const achievements = [];
		for (const achievementName of achievementNames) {
			achievements.push(
				await this.prisma.achievement.findUnique({
					where: {
						name: achievementName.achievementName,
					},
					select: {
						name: true,
						description: true,
						picture: true,
					},
				}),
			);
		}
		return achievements;
	}

	//TODO
	//DONE	1 : modify Plays table and Migrate
	//DONE	2 : finish this endpoint
	//DONE but improve	2.1 : AVOID USING STORE in front
	//DONE		2.2: MatchHistory: use Server Side table with seb socket (socket.io)
	//DONE	5 : Do 2FA auth on the frontend
	//DONE	7 : Implement Logout
	//DONE	8 : add type spec to this endpoint handler
	//?	3 : Add "insert into Achievements.." script by hand
	//?	4 : TEST
	//?	7 : Handle Images url to png (or blob) files in db
	//?	6 : Rethink Vue pinia Stores.
	async getAllGames(
		userID: number,
		limit: number = Infinity,
	): Promise<
		{
			createdAt: Date;
			host: string;
			guest: string;
			host_score: number;
			guest_score: number;
		}[]
	> {
		if (debug) console.log(`DEBUG | Players.Service | getAllGames | userID: ${userID}`);
		const gamesAsHost = await this.prisma.plays.findMany({
			where: {
				hostID: userID,
			},
			select: {
				createdAt: true,
				hostID: true,
				guestID: true,
				score_host: true,
				score_Guest: true,
			},
		});
		const gamesAsGuest = await this.prisma.plays.findMany({
			where: {
				guestID: userID,
			},
			select: {
				createdAt: true,
				guestID: true,
				hostID: true,
				score_host: true,
				score_Guest: true,
			},
		});

		let games = [];
		for (const game of gamesAsHost) {
			games.push({
				createdAt: game.createdAt,
				host: (await this.findOne(game.hostID)).username,
				guest: (await this.findOne(game.guestID)).username,
				host_score: game.score_host,
				guest_score: game.score_Guest,
			});
		}
		for (const game of gamesAsGuest) {
			games.push({
				createdAt: game.createdAt,
				host: (await this.findOne(game.hostID)).username,
				guest: (await this.findOne(game.guestID)).username,
				host_score: game.score_host,
				guest_score: game.score_Guest,
			});
		}
		games = games.slice(0, limit);
		// const games = gamesAsGuest
		// 	.map(async (el) => {
		// 		host: (await this.findOne(el.hostID)).username;
		// 		guest: (await this.findOne(el.guestID)).username;
		// 		host_score: el.score_host;
		// 		guest_score: el.score_Guest;
		// 	})
		// 	.concat(
		// 		gamesAsHost.map(async (el) => {
		// 			host: (await this.findOne(el.hostID)).username;
		// 			guest: (await this.findOne(el.guestID)).username;
		// 			host_score: el.score_host;
		// 			guest_score: el.score_Guest;
		// 		}),
		// 	)
		// 	.slice(0, limit);
        if (debug) console.log(`DEBUG | Players.Service | getAllGames | games : ` + games);

		return games;
	}

	// async addFriend(recpientID: number, requestorID: number) {}

	// async acceptFriendship(recpientID: number, requestorID: number) {}

	// async getChats(
	// 	id: number,
	// 	limit: number,
	// ): Promise<
	// 	{
	// 		name: string;
	// 		dm: boolean;
	// 		avatar: string;
	// 	}[]
	// > {
	// 	if (debug) console.log(id);
	// 	if (debug) console.log(limit);

	// 	// this.prisma.

	// 	return [
	// 		{
	// 			name: '',
	// 			dm: false,
	// 			avatar: '',
	// 		},
	// 		{
	// 			name: '',
	// 			dm: false,
	// 			avatar: '',
	// 		},
	// 	];
	// }
}
