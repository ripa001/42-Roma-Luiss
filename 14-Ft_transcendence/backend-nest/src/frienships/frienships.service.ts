import { Injectable } from '@nestjs/common';
import { CreateFrienshipDto } from './dto/create-frienship.dto';
import { UpdateFrienshipDto } from './dto/update-frienship.dto';
import { PrismaService } from 'src/prisma/prisma.service';
import { BeFriends, Player } from '@prisma/client';
import { SendFriendshipRequestDto } from './dto/send-friendship-request.dto';

const debug = false

@Injectable()
export class FrienshipsService {

	constructor(private readonly prisma: PrismaService) {}

	async createFrienshipRequest(userID : number, recipientID: number): Promise<SendFriendshipRequestDto> {
		
		const requestor = await this.prisma.player.findUnique({
			where: {
				id: userID
			},
			select: {
				id: true,
				username: true,
				avatar: true
			}
		});
		const [existingReqID, existingRecipID] = await this.getFriendship(userID, recipientID);
		if (debug) console.log(`existingReqID: ${existingReqID}; existingReqID: ${existingReqID}`);
		let friendship: BeFriends | null = null 
		if (undefined != existingReqID)
			friendship = await this.prisma.beFriends.findUnique({
				where: {
					requestorID_recipientID: {
						requestorID: existingReqID,
						recipientID: existingRecipID
					},
				},
			});

		/**
		 * A friendship request may only be sent when the friendship
		 * relation instance does not exist
		 * 
		 * A friendship relation instance might exist when:
		 *	1. the friendship request is pending
		 *	2. a user blocked another user
		 */
		if (friendship) {
			if (friendship.recipient_blacklisted || friendship.requestor_blacklisted)
				throw Error('friendships requests cannot be among blocked users (both ways)');
			throw Error('friendship request already exist');
		}
		
		await this.prisma.beFriends.create({
			data: {
				requestorID: userID,
				recipientID: recipientID
			},
		})
		return {
			requestorID: requestor.id,
			requestorUsername: requestor.username,
			requestorAvatar: `players/avatar/${requestor.id}`
		};
	}

	async findAllFrienshipRequests(userID: number): Promise<SendFriendshipRequestDto[]> {
		const requestorsIDs = await this.prisma.beFriends.findMany({
				where: {
					recipientID: userID,
					are_friends: false,
					pending_friendship: true,
				},
				select: {
					requestorID: true,
				},
		});

		let requestors: SendFriendshipRequestDto[] = [];
		let recordFound: any;
		for (let requestorID of requestorsIDs) {
			recordFound = await this.prisma.player.findUnique({
				where: {
					id: requestorID.requestorID
				},
				select: {
					id: true,
					username: true,
					avatar: true
				}
			});
			if (null != recordFound)
				requestors.push({
					requestorID: recordFound.id,
					requestorUsername: recordFound.username,
					requestorAvatar: `players/avatar/${recordFound.id}`
				});
		}
		return requestors;
	}

	/**
	 * this function toggles the block unlock of a user.
	 * It modifies the friendship record, first crating if not yet existent,
	 * following the db business rules that can be found in table constraints script (BeFriend table)
	 * 
	 * @param userID the user calling the websocket
	 * @param friendID the user to block/unblock
	 * @param block toggle variable to block/unblock user
	 * @returns Promise<number[]>: the updated requestorID and recipientID if record is initially non existent
	 */
	async toggleBlockUser(
		userID: number, friendID: number,
		requestorID: number, recipientID: number,
		block: boolean
	): Promise<number[]> {

		let friendship: BeFriends;

		if (undefined == requestorID) {
			if (debug) console.log(`creating friendship record`);
			await this.prisma.beFriends.create({
				data: {
					are_friends: false,
					pending_friendship: false,
					requestor_blacklisted: false,
					recipient_blacklisted: block,
					requestorID: userID,
					recipientID: friendID,
				}
			});
			requestorID = userID;
			recipientID = friendID;
		}
		else if (requestorID == userID)
			await this.prisma.beFriends.update({
				where: {
					requestorID_recipientID: {
						requestorID,
						recipientID
					}
				},
				data: {
					are_friends: false,
					pending_friendship: false,
					recipient_blacklisted: block
				}
			});
		else if (recipientID == userID)
			await this.prisma.beFriends.update({
				where: {
					requestorID_recipientID: {
						requestorID,
						recipientID
					}
				},
				data: {
					are_friends: false,
					pending_friendship: false,
					requestor_blacklisted: block
				}
			});
		else
			throw Error('could not find friendship for these requestor and recipient');

		friendship = await this.prisma.beFriends.findUnique({
			where: {
				requestorID_recipientID: {
					requestorID: requestorID,
					recipientID:recipientID
				}
			}
		});
		if (
			false == friendship.requestor_blacklisted &&
			false == friendship.recipient_blacklisted
		)
			await this.prisma.beFriends.delete({
				where: {
					requestorID_recipientID: {
						requestorID: requestorID,
						recipientID: recipientID
					}
				}
			});
		
		return [requestorID, recipientID];
	}
	
	// async updateFrienshipRequest(updateFrienshipDto: UpdateFrienshipDto): Promise<BeFriends> {
	// 	return await this.prisma.beFriends.update({
	// 		where: {
	// 			requestorID_recipientID: {
	// 				requestorID: updateFrienshipDto.requestorID,
	// 				recipientID: updateFrienshipDto.recipientID
	// 			}
	// 		},
	// 		data: {
	// 			are_friends: updateFrienshipDto.are_friends,
	// 			pending_friendship: updateFrienshipDto.pending_friendship,
	// 			requestor_blacklisted: updateFrienshipDto.requestor_blacklisted,
	// 			recipient_blacklisted: updateFrienshipDto.recipient_blacklisted,
	// 		}
	// 	});
	// }

	async acceptFriendshipRequest(requestorID: number, recipientID: number) {
		const friendship = await this.prisma.beFriends.findUnique({
			where: {
				requestorID_recipientID: {requestorID, recipientID}
			}
		});

		if (friendship && friendship.pending_friendship) {
			if (debug) console.log(`updating the db with requestorID: ${requestorID}; recipientID: ${recipientID}`)
			await this.prisma.beFriends.update({
				where: {
					requestorID_recipientID: {requestorID, recipientID}
				},
				data: {
					are_friends: true,
					pending_friendship: false,
					requestor_blacklisted: false,
					recipient_blacklisted: false
				}
			});

			const friendship_achievement = await this.prisma.achieved.findMany({
				where: {
					OR: [
						{playerID: requestorID},
						{playerID: recipientID},
					],
					achievementName: 'Chi trova un amico, trova un tesoro'
				}
			});
			if (0 === friendship_achievement.length) {
				await this.prisma.achieved.create({
					data: {
						playerID: requestorID,
						achievementName: 'Chi trova un amico, trova un tesoro',
						date_of_issue: new Date()
					}
				});
				await this.prisma.achieved.create({
					data: {
						playerID: recipientID,
						achievementName: 'Chi trova un amico, trova un tesoro',
						date_of_issue: new Date()
					}
				});
			}
		}
		else
			throw Error('no pending request');
	}

	async deleteFrienshipRequest(requestorID: number, recipientID: number) {

		// console.log(`GATEWAY SERVICE | friendships deleteFrienshipRequest | BEGIN`);

		if (undefined == requestorID) {
			// console.log(`GATEWAY SERVICE | friendships deleteFrienshipRequest | friendship NOT FOUND for requestorID:${requestorID}, recipientID:${recipientID}`);
			throw Error('Could not find friendhip');
		}

		// console.log(`GATEWAY SERVICE | friendships deleteFrienshipRequest | looking for friendship in prisma db: requestorID:${requestorID}, recipientID:${recipientID}`);
		const friendship = await this.prisma.beFriends.findUnique({
			where: {
				requestorID_recipientID: {
					requestorID,
					recipientID
				}
			}
		});
		// console.log(`GATEWAY SERVICE | friendships deleteFrienshipRequest | found friendship requestorID:${requestorID}, recipientID:${recipientID}`);

		if (friendship.requestor_blacklisted || friendship.recipient_blacklisted)
		{
			// console.log(`cannot delete friendship among blocked users`);
			throw Error("Cannot delete friendship among blocked users")
		}
		
		await this.prisma.beFriends.delete({
			where: {
				requestorID_recipientID: {
					requestorID,
					recipientID
				}
			}
		});
		// console.log(`friendship successfully deleted`);
		// console.log(`GATEWAY SERVICE | friendships deleteFrienshipRequest | END`);
	}

	//Helpers

	async getFriendship(userID: number, friendID: number): Promise<number[]> {
		// console.log(`GATEWAY SERVICE | friendships getFriendship | BEGIN`);

		if (
			await this.prisma.beFriends.findUnique({
				where: {
					requestorID_recipientID: {
						requestorID: userID,
						recipientID: friendID
					}
				}
			})
		) {
			// console.log(`GATEWAY SERVICE | friendships getFriendship | found friendship requestorID:${userID}, recipientID:${friendID}`);
			return [userID, friendID];
		}
		else if (
			await this.prisma.beFriends.findUnique({
				where: {
					requestorID_recipientID: {
						requestorID: friendID,
						recipientID: userID
					}
				}
			})
		) {
			// console.log(`GATEWAY SERVICE | friendships getFriendship | found friendship requestorID:${friendID}, recipientID:${userID}`);
			return [friendID, userID];
		}
		else {
			// console.log(`GATEWAY SERVICE | friendships getFriendship | friendship not found for userID:${userID}, friendID:${friendID}`);
			return [];
		}
	}

}
