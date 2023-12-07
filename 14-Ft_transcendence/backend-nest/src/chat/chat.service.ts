import { Injectable } from '@nestjs/common';
import { CreateChatDto } from './dto/create-chat.dto';
import { CreateGroupDto } from './dto/create-group.dto';
import { UpdateGroupDto } from './dto/update-group.dto';
import { PrismaService } from 'src/prisma/prisma.service';
import * as bcrypt from 'bcrypt';
import * as dotenv from 'dotenv';
import { of } from 'rxjs';

const saltRounds = 10;

dotenv.config();

// const iv = process.env.SALT;



@Injectable()
export class ChatService {
  constructor(private readonly prisma: PrismaService) { }

  async createChatRoomMessage(createChatDto: CreateChatDto) {
    createChatDto.receiverID = null;
    createChatDto.receiversID = Number(createChatDto.receiversID);
    try {
      const res1 = await this.prisma.subscribed.findMany({
        where: {
          playerID: createChatDto.senderID,
          chatroomID: createChatDto.receiversID,
          OR: [
            {
              isBanned: true,
            },
            {
              isMuted: true,
            },
          ],
        },
      });
      if (res1.length > 0)
        return null;
      const res = await this.prisma.message.create({
        data: {
          content: createChatDto.content,
          timestamp: createChatDto.createdAt,
          sender: {
            connect: {
              id: createChatDto.senderID,
            },
          },
          receivers: {
            connect: {
              groupID: createChatDto.receiversID,
            },
          },
        },
      });
      await this.prisma.chatRoom.update({
        where: {
          groupID: createChatDto.receiversID,
        },
        data: {
          messages: {
            connect: {
              messageID: res.messageID,
            },
          },
        },
      });
      const result = await this.prisma.chatRoom.findUnique({
        where: {
          groupID: createChatDto.receiversID,
        },
        select: {
          subscriptions: {
            select: {
              playerID: true,
            },
            where: {
              isBanned: false,
              playerID: {
                not: createChatDto.senderID,
              },
            },
          },
        },
      });
      const senderName = await this.prisma.player.findUnique({
        where: {
          id: createChatDto.senderID,
        },
        select: {
          username: true,
        },
      });
      return result.subscriptions.map((subscription) => ({
        ...subscription,
        senderName: senderName.username,
      }));
    } catch (error) {
      console.error(error);
      return null;
    }
  }

  async createChatMessage(createChatDto: CreateChatDto) {
    createChatDto.receiverID = Number(createChatDto.receiverID);
    createChatDto.receiversID = null;
    let senderName = null;
    try {
      let isBlocked = await this.prisma.beFriends.findMany({
          where: {
            OR: [
              {
                requestorID: createChatDto.senderID,
                recipientID: createChatDto.receiverID,
                requestor_blacklisted: true,
              },
              {
                recipientID: createChatDto.senderID,
                requestorID: createChatDto.receiverID,
                recipient_blacklisted: true,
              },
            ],
          },
          select: {
            requestorID: true,
            recipientID: true,
          },
        });
      if (isBlocked.length > 0)
        return null
      const res = await this.prisma.message.create({
        data: {
          content: createChatDto.content,
          timestamp: createChatDto.createdAt,
          sender: {
            connect: {
              id: createChatDto.senderID,
            },
          },
          receiver: {
            connect: {
              id: createChatDto.receiverID,
            },
          },
        },
      });
      senderName = await this.prisma.player.findUnique({
        where: {
          id: createChatDto.senderID,
        },
        select: {
          username: true,
        },
      });

    } catch (error) {
      // Handle errors here
      console.error(error);
      return null; // Rethrow the error or handle it as needed
    }
    return {"playerID": createChatDto.receiverID};

  }

  async create(createChatDto: CreateChatDto, isMutedId: number): Promise<any> {
    createChatDto.senderID = Number(createChatDto.senderID);

    if (createChatDto.receiversID) {
      let isMember = await this.prisma.subscribed.findMany({
        where: {
          playerID: createChatDto.senderID,
          chatroomID: createChatDto.receiversID,
        },
      });
      if (isMember.length === 0)
        return "isMuted"
      let isMuted = await this.prisma.subscribed.findMany({
        where: {
          playerID: isMutedId,
          chatroomID: createChatDto.receiversID,
          OR: [
            {
              isBanned: true,
            },
            {
              isMuted: true,
            },
          ],
        },
      });
      if (isMuted.length > 0)
        return "isMuted";
      return await this.createChatRoomMessage(createChatDto);
    } else if (createChatDto.receiverID)
      return [await this.createChatMessage(createChatDto)];
    else
      return null;
  }

  async getBlockedUsers(userId: number) {
    let res = await this.prisma.beFriends.findMany({
      where: {
        OR: [
          {
            requestorID: userId,
            requestor_blacklisted: true,
          },
          {
            recipientID: userId,
            recipient_blacklisted: true,
          },
        ],
      },
      select: {
        requestorID: true,
        recipientID: true,
      },
    });
    let blockedUsers = res.map((user) => {
      return user.requestorID === userId ? user.recipientID : user.requestorID;
    });
    return blockedUsers;
  }

  async createGroupChat(group: CreateGroupDto) {
    const { name, members, founderId, visibility, password } = group;
    const chatGroup = await this.prisma.chatRoom.create({
      data: {
        name,
        founder: { connect: { id: founderId } },
        visibility: visibility === "public" ? "public" : visibility === "private" ? "private" : visibility === "protected" ? "protected" : "private",
        password: visibility === "protected" ? await bcrypt.hash(password, saltRounds) : "",
        subscriptions: {
          create: members.map((memberId) => ({
            isAdmin: memberId === founderId,
            isMuted: false,
            isBanned: false,
            player: { connect: { id: Number(memberId) } },
          })),
        },
      }
    });

    return chatGroup;
  }

  async addUsersToGroup(groupId: number, userIds: number[], adminId: number) {
    let isAdminId = await this.prisma.subscribed.findMany({
      where: {
        chatroomID: groupId,
        isAdmin: true,
        playerID: adminId,
      },
      select: {
        playerID: true,
      },
    });
    if (isAdminId.length === 0)
      return null;
    try {
      const res = await this.prisma.chatRoom.update({
        where: {
          groupID: groupId,
        },
        data: {
          subscriptions: {
            create: userIds.map((userId) => ({
              isAdmin: false,
              isMuted: false,
              isBanned: false,

              player: { connect: { id: userId } },
            }),
            ),
          },
        },
      });
      return await this.prisma.chatRoom.findUnique({
        where: {
          groupID: groupId,
        },
        select: {
          name: true,
          messages: {
            take: 1,
            orderBy: { timestamp: 'desc' },
          },
          subscriptions: {
            select: {
              player: true,
            },
          },
        },
      });
    } catch (error) {
      console.error(error);
      throw error;
    }
  }

  async editUserSubscription(userId: number, groupId: number, isAdmin: boolean, isMuted: boolean, isBanned: boolean, adminId: number) {
    let isAdminId = await this.prisma.subscribed.findMany({
      where: {
        chatroomID: groupId,
        isAdmin: true,
        playerID: adminId,
      },
      select: {
        playerID: true,
      },
    });
    if (isAdminId.length === 0)
      return null;
    //  check if user is owner
    let isOwner = await this.prisma.chatRoom.findMany({
      where: {
        groupID: groupId,
        founderID: userId,
      },
      select: {
        founderID: true,
      },
    });
    if (isOwner.length > 0)
      return null;
    let res = await this.prisma.subscribed.update({
      where: {
        playerID_chatroomID: {
          playerID: userId,
          chatroomID: groupId,
        },
      },
      data: {
        isAdmin: isAdmin,
        isMuted: isMuted,
        isBanned: isBanned,
      }
    });
    return await this.prisma.subscribed.findMany({
      where: {
        chatroomID: groupId,
      },
      select: {
        playerID: true,
      },
    });
  }

  async removeUserFromGroup(userId: number, groupId: number, adminId: number) {
    try {
        if (userId != adminId) {
        let isAdminId = await this.prisma.subscribed.findMany({
          where: {
            chatroomID: groupId,
            isAdmin: true,
            playerID: adminId,
          },
          select: {
            playerID: true,
          },
        });
        if (isAdminId.length === 0) {
          return ["bad request"];
        }
        let isOwner = await this.prisma.chatRoom.findMany({
          where: {
            groupID: groupId,
            founderID: userId,
          },
          select: {
            founderID: true,
          },
        });
        if (isOwner.length > 0) {
          return ["bad request"];
        }
      }
      let res = await this.prisma.subscribed.findMany({
        where: {
          chatroomID: groupId,
          isAdmin: true,
          playerID: {
            not: userId,
          },
        },
        select: {
          playerID: true,
        },
      });
      if (res.length === 0) {
        let res2 = await this.prisma.subscribed.findMany({
          where: {
            chatroomID: groupId,
            playerID: {
              not: userId,
            },
          },
          select: {
            playerID: true,
            isMuted: true,
            isBanned: true,
          },
        });
        
        let users = res2.filter((user) => {
          return user.isBanned === false;
        });
        if (users.length !== 0) {
          let randomAdmin = users[Math.floor(Math.random() * users.length)];
          await this.prisma.subscribed.update({
            where: {
              playerID_chatroomID: {
                playerID: randomAdmin.playerID,
                chatroomID: groupId,
              },
            },
            data: {
              isAdmin: true,
            },
          });
        }

      }
      await this.prisma.chatRoom.update({
        where: {
          groupID: groupId,
        },
        data: {
          subscriptions: {
            delete: {
              playerID_chatroomID: {
                playerID: userId,
                chatroomID: groupId,
              },
            },
          },
        },
      });
      let res2 = await this.prisma.subscribed.findMany({
        where: {
          chatroomID: groupId,
        },
        select: {
          playerID: true,
        },
      });
      if (res2.length === 0) {
        return ["delete group"]
      }
      return res2;
    } catch (error) {
      console.error(error);
    }
  }

  findAll() {
    return this.prisma.message.findMany();
  }

  findChatandMessageByUserId(userId: number) {
    console.log(`DEBUG | chat.service | findChatandMessageByUserId | userId: ${userId}`);
    return this.prisma.message.findMany({
      where: {
        OR: [
          {
            senderID: userId,
          },
          {
            receiverID: userId,
          },
        ],
      },
    });
  }

  async getParents(userId: number) {
    const user = await this.prisma.player.findUnique({
      where: { id: userId },
      include: {
        sentFriendshipRequests: {
          where: { are_friends: true },
          select: {
            recipient: {
              select: {
                id: true,
                username: true,
                avatar: true,
              },
            },
            requestor: {
              select: {
                id: true,
                username: true,
                avatar: true,
              },

            },

          },
        },
        receivedFriendshipRequests: {
          where: { are_friends: true },
          select: {
            recipient: {
              select: {
                id: true,
                username: true,
                avatar: true,
              },
            },
            requestor: {
              select: {
                id: true,
                username: true,
                avatar: true,
              },
            },
          },
        },
        chatroomSubscriptions: {
          select: {
            chatroom: {
              select: {
                groupID: true,
                name: true,
                founder: {
                  select: {
                    username: true,
                  },
                },
                messages: {
                  take: 1,
                  orderBy: { timestamp: 'desc' },
                },
                createdAt: true,
                },
              }
            },
            where: {
              isBanned: false,
            },
          },
        },
    });
    
    let listoffriends = [];
    for (const friendship of user.sentFriendshipRequests.concat(user.receivedFriendshipRequests)) {
      if (friendship.requestor.id === userId)
        listoffriends.push(friendship.recipient);
      else
        listoffriends.push(friendship.requestor);
      listoffriends[listoffriends.length - 1].lastMessage = await this.prisma.message.findMany({
        where: {
          OR: [
            {
              senderID: userId,
              receiverID: listoffriends[listoffriends.length - 1].id,
            },
            {
              senderID: listoffriends[listoffriends.length - 1].id,
              receiverID: userId,
            },
          ],
        },
        take: 1,
        orderBy: { timestamp: 'desc' },
      });
    }
    
    
    const friends = listoffriends.map((friendship) => ({
      id: friendship.id,
      name: friendship.username,
      lastMessage: friendship.lastMessage.length > 0 ? friendship.lastMessage[0].timestamp : null,
      isGroup: false,
      avatar: "/players/avatar/" + friendship.id,
    }));

    const roomsWithLastMessage = user.chatroomSubscriptions.map((room) => ({
      id: room.chatroom.groupID,
      name: room.chatroom.name,
      lastMessage: room.chatroom.messages.length > 0 ? room.chatroom.messages[0].timestamp : room.chatroom.createdAt,
      isGroup: true,
    }));

    const sortedData = [...friends, ...roomsWithLastMessage].sort((a, b) => {
      if (!('lastMessage' in a) && !('lastMessage' in b)) {
        return 0;
      } else if (!('lastMessage' in a)) {
        return 1;
      } else if (!('lastMessage' in b)) {
        return -1;
      } else {
        return ((b.lastMessage as Date) || new Date(0)).getTime() - ((a.lastMessage as Date) || new Date(0)).getTime();
      }
    });
    return { friends: friends, rooms: roomsWithLastMessage, sortedData: sortedData };
  }

  async getGroupInfo(groupId: number, userId: number) {
    console.log(`DEBUG | chat.service | getGroupInfo | groupId: ${groupId}`);

    let isInGroup = await this.prisma.subscribed.findMany({
      where: {
        chatroomID: groupId,
        playerID: userId,
      },
      select: {
        playerID: true,
      },
    });
    if (isInGroup.length === 0) {
      return {error: "not in group"};
    }
    const group = await this.prisma.chatRoom.findUnique({
      where: { groupID: groupId },
      select: {
        groupID: true,
        name: true,
        visibility: true,
        founder: {
          select: {
            username: true,
          },
        
        },
        subscriptions: {
          select: {
            player: {
              select: {
                id: true,
                username: true,
              },
            },
            isAdmin: true,
            isMuted: true,
            isBanned: true,
          },
          
        },
      },
    });
    return {
      id: group.groupID,
      name: group.name,
      founder: group.founder.username,
      visibility: group.visibility,
      members: group.subscriptions.map((subscription) => ({
        id: subscription.player.id,
        name: subscription.player.username,
        isAdmin: subscription.isAdmin,
        isMuted: subscription.isMuted,
        isBanned: subscription.isBanned,
      })),
    };
  }

  async getFriendsNotInGroup(userId: number, groupId: number) {
    const group = await this.prisma.chatRoom.findUnique({
      where: { groupID: groupId },
      include: {
        subscriptions: {
          select: {
            playerID: true,
          },
        },
      },
    });
  
    const friends = await this.prisma.player.findMany({
      where: { id: userId },
      include: {
        sentFriendshipRequests: {
          where: { are_friends: true },
          select: {
            recipient: {
              select: {
                id: true,
                username: true,
                avatar: true,
              },
            },
            requestor: {
              select: {
                id: true,
                username: true,
              },
            },
          },
        },
        receivedFriendshipRequests: {
          where: { are_friends: true },
          select: {
            recipient: {
              select: {
                id: true,
                username: true,
                avatar: true,
              },
            },
            requestor: {
              select: {
                id: true,
                username: true,
              },
            },
          },
        },

      },
    });
    let newFriends = [];
    for (const friendship of friends[0].sentFriendshipRequests.concat(friends[0].receivedFriendshipRequests)) {
      if (friendship.requestor.id === userId)
        newFriends.push(friendship.recipient);
      else
        newFriends.push(friendship.requestor);
      
    }
    const friendsNotInGroup = newFriends.filter((friend) => {
      return !group.subscriptions.some((subscription) => {
        return subscription.playerID === friend.id;
      });
    });
    return { friends: friendsNotInGroup };
  }

  async getMessagesPrivateChat(me: number, friend: number) {
    console.log(`DEBUG | chat.service | getMessagesPrivateChat | me: ${me} | friend: ${friend}`);
    let isBlocked = await this.prisma.beFriends.findMany({
      where: {
        OR: [
          {
            requestorID: me,
            recipientID: friend,
            requestor_blacklisted: true,
          },
          {
            recipientID: me,
            requestorID: friend,
            recipient_blacklisted: true,
          },
          {
            recipientID: me,
            requestorID: friend,
            requestor_blacklisted: true,
          },
          {
            requestorID: me,
            recipientID: friend,
            recipient_blacklisted: true,
          },
        ]
      },
    })
    if (isBlocked.length > 0)
      return { isBlocked: true };
    
    let res = await this.prisma.message.findMany({
      where: {
        OR: [
          {
            senderID: me,
            receiverID: friend,
          },
          {
            senderID: friend,
            receiverID: me,
          },
        ],
      },
    });
    console.log(`DEBUG | chat.service | getMessagesPrivateChat | res: ${res}`); // [object PrismaPromise]

    let res1 = await res.map((message) => ({
      ...message,
    }));
    return { messages: res1, subscriptions: null };
  }

  async getMessagesGroupChat(me: number, group: number) {
    console.log(`DEBUG | chat.service | getMessagesGroupChat | me: ${me} | group: ${group}`);

    let res = await this.prisma.chatRoom.findUnique({
      where: {
        groupID: group,
      },
      include: {
        messages: {
          include: {
            sender: {
              select: {
                id: true,
                username: true,
              },

            
            },
          },
          orderBy: { timestamp: 'asc' },
        },
        subscriptions: {
          select: {
            playerID: true,
            isAdmin: true,
            isMuted: true,
            isBanned: true
          }

        },

      }
    });
    let blocked_users = await this.prisma.beFriends.findMany({
      where: {
        OR: [
          {
            requestorID: me,
            requestor_blacklisted: true,
          },
          {
            recipientID: me,
            requestor_blacklisted: true,
          },
          {
            recipientID: me,
            recipient_blacklisted: true,
          },
          {
            requestorID: me,
            recipient_blacklisted: true,
          },
        ],
      },
      select: {
        requestorID: true,
        recipientID: true,
      },
    });

    res.messages.forEach((message) => {
      if (blocked_users.some((user) => {
        let id = user.requestorID === me ? user.recipientID : user.requestorID;
        return id === message.sender.id;
        // return user.requestorID === message.sender.id || user.recipientID === message.sender.id;
      }))
        message.content = "This message is blocked";
    });
    let ret1 = res.messages.map((message) => ({
      ...message,
      senderName: message.sender.username,
    }));
    let ret2 = res.subscriptions.map((subscription) => ({
      ...subscription,
      playerID: subscription.playerID,
      isAdmin: subscription.isAdmin,
      isMuted: subscription.isMuted,
      isBanned: subscription.isBanned,

    }));
    return { messages: ret1, subscriptions: ret2 };
  }

  async searchGroups(groupSearch: string, userId: number) {
    console.log(`DEBUG | chat.service | searchGroups | groupSearch: ${groupSearch}, userId: ${userId}`);
    // select where name contains groupSearch and is public or protected and user is not in group members
    let res = await this.prisma.chatRoom.findMany({
      where: {
        name: {
          contains: groupSearch,
          
        },
        OR: [
          {
            visibility: "public",
          },
          {
            visibility: "protected",
          },
        ],
        subscriptions: {
          none: {
            playerID: userId,
          },
        },
      },
      select: {
        groupID: true,
        name: true,
        founder: {
          select: {
            username: true,
          },
        },
        subscriptions: {
          select: {
            playerID: true,
          },
        },
        visibility: true,
      },
    });
    
    let ret = res.map((group) => ({
      ...group,
      founder: group.founder.username,
      members: group.subscriptions.map((subscription) => ({
        ...subscription,
        playerID: subscription.playerID,
      })),
      password: ""

    }));
    console.log(`DEBUG | chat.service | searchGroups | ret: ${ret.length}`);
    
    return { groups: ret };
  }

  async joinGroup(groupId: number, userId: number, password: string) {
    console.log(`DEBUG | chat.service | joinGroup | groupId: ${groupId} | userId: ${userId} | password: ${password}`);
    let res = await this.prisma.chatRoom.findUnique({
      where: {
        groupID: groupId,
      },
      select: {
        visibility: true,
        password: true,
      },
    });
    console.log(`DEBUG | chat.service | joinGroup | res: ${res}`);
    if (res.visibility === "public" || (res.visibility === "protected" && await bcrypt.compare(password, res.password))) {
      
      await this.prisma.chatRoom.update({
        where: {
            groupID: groupId,
        },
        data: {
          subscriptions: {
            create: [{
              isAdmin: false,
              isMuted: false,
              isBanned: false,
              player: {
                connect: {
                  id: userId,
                },
              },
              
            }],
          },
        },
      });
      return await this.prisma.chatRoom.findUnique({
        where: {
          groupID: groupId,
        },
        select: {
          name: true,
          messages: {
            take: 1,
            orderBy: { timestamp: 'desc' },
          },
          subscriptions: {
            select: {
              player: true,
            },
          },
        },
      });
    }
    else
      return null;
  }

  async editGroup(group: UpdateGroupDto, userId: number) {
    let isAdminId = await this.prisma.subscribed.findMany({
      where: {
        chatroomID: group.id,
        isAdmin: true,
        playerID: userId,
      },
      select: {
        playerID: true,
      },
    });
    if (isAdminId.length === 0)
      return null;
    
    await this.prisma.chatRoom.update({
      where: {
        groupID: group.id,
      },
      data: {
        name: group.name,
        visibility: group.visibility === "public" ? "public" : group.visibility === "private" ? "private" : group.visibility === "protected" ? "protected" : "private",
        password: group.visibility === "protected" ? await bcrypt.hash(group.password, saltRounds) : "",
      },
    });
    return { success: true };
  }
}
