import { WebSocketGateway, SubscribeMessage, MessageBody, ConnectedSocket, WebSocketServer } from '@nestjs/websockets';
import { Socket, Server } from 'socket.io';
import { ChatService } from './chat.service';
import { CreateGroupDto } from './dto/create-group.dto';
import { CreateChatDto } from './dto/create-chat.dto';
import { UpdateGroupDto } from './dto/update-group.dto';
import { JwtService } from '@nestjs/jwt';
import { async } from 'rxjs';
import { response } from 'express';
import { group } from 'console';
import { UseFilters, UsePipes, ValidationPipe } from '@nestjs/common';

const debug = false;

import { ArgumentsHost, Catch, HttpException } from '@nestjs/common';
import { WsException } from '@nestjs/websockets';

@Catch(WsException, HttpException)
export class WsExceptionFilter {
  public catch(exception: HttpException, host: ArgumentsHost) {
    const client = host.switchToWs().getClient();
    this.handleError(client, exception);
  }

  public handleError(client: Socket, exception: HttpException | WsException) {
    if (exception instanceof HttpException) {
      if (debug) console.log(`DEBUG | chat.gateway | handleError | HttpException: ${exception}`);
    } else {
      if (debug) console.log(`DEBUG | chat.gateway | handleError | WsException: ${exception}`);
    }
  }
}

@UseFilters(WsExceptionFilter)
@WebSocketGateway({
  cors: {
    origin: '*',
  },
  namespace: "chat"
})
export class ChatGateway {
  @WebSocketServer()
  server: Server
  private clients: Map<number, Socket>;

  constructor(
    private readonly chatService: ChatService,
    private readonly jwtService: JwtService
  ) {
    this.clients = new Map<number, Socket>();
  }


  async handleConnection(client: any, ...args: any[]) {
    try {
      const user = await this.jwtService.verifyAsync(client.handshake.auth.token, {
        secret: process.env.JWT_SECRET
      });
      this.clients.set(Number(user.sub), client);
    } catch (error) {
      if (debug) console.log(`DEBUG | chat.gateway | handleConnection | error: ${error}`);
      client.emit('redirect', '/login');
    }
  }

  handleDisconnect(client: any) {
    let id;

    for (let [userID, csock] of this.clients) {
			if (client.id == csock.id) {
        id = userID;
        break ;
			}

		}
    this.clients.delete(id);
  }

  @SubscribeMessage('findAllChat')
  findAll() {
    return this.chatService.findAll();
  }

  @SubscribeMessage("join")
  joinRoom() {
    if (debug) console.log("join");
  }

  @SubscribeMessage("getmessages")
  getMessages(@MessageBody("userId") userId: string, @MessageBody("chatId") chatId: string, @MessageBody("isGroup") isGroup: string) {
    if (debug) console.log(`DEBUG | chat.controller | getMessagesPrivateChat | userId: ${userId}`);
    if (isGroup)
      return this.chatService.getMessagesGroupChat(Number(userId), Number(chatId));
    else
      return this.chatService.getMessagesPrivateChat(Number(userId), Number(chatId));
  }

  @SubscribeMessage("getparents")
  getParents(@MessageBody("userId") userId: string) {
    if (debug) console.log(`DEBUG | chat.controller | getParents | userId: ${userId}`);
    return this.chatService.getParents(Number(userId));
  }

  @SubscribeMessage("getfriendsnotingroup")
  getFriendsNotInGroup(@MessageBody("userId") userId: string, @MessageBody("groupId") groupId: string) {
    if (debug) console.log(`DEBUG | chat.controller | getFriendsNotInGroup | userId: ${userId}`);
    return this.chatService.getFriendsNotInGroup(Number(userId), Number(groupId));
  }

  @SubscribeMessage("getgroupinfo")
  getGroupInfo(@MessageBody("groupId") groupId: string, @ConnectedSocket() client: Socket) {
    if (debug) console.log(`DEBUG | chat.controller | getGroupInfo | groupId: ${groupId}`);
    let userId = this.jwtService.decode(client.handshake.auth.token)['sub'];
    return this.chatService.getGroupInfo(Number(groupId), Number(userId));
  }

  @SubscribeMessage("editusersubscription")
  editUserSubscription(@MessageBody("userId") userId: string, @MessageBody("groupId") groupId: string, @MessageBody("isAdmin") isAdmin: boolean, @MessageBody("isMuted") isMuted: boolean, @MessageBody("isBanned") isBanned: boolean, @ConnectedSocket() client: Socket) {
    if (debug) console.log(`DEBUG | chat.controller | editUserSubscription | userId: ${userId}`);
    let adminId = this.jwtService.decode(client.handshake.auth.token)['sub'];
    if (debug) console.log(`DEBUG | chat.controller | editUserSubscription | adminId: ${adminId}`);
    this.chatService.editUserSubscription(Number(userId), Number(groupId), isAdmin, isMuted, isBanned, Number(adminId)).then(response => {
      if (!response)
        return { success: false };
      response.forEach((memberId) => {
        if (debug) console.log(`DEBUG | chat.controller | editUserSubscription | memberId: ${memberId.playerID}`);
        let recClientId = this.clients.get(Number(memberId.playerID));

        if (recClientId)
          this.server.to(`${recClientId.id}`).emit('editusersubscription', { userId, groupId, isAdmin, isMuted });
      }
      )
    });
    return { success: true };
  }

  @SubscribeMessage("addusertogroup")
  addUserToGroup(@MessageBody("groupId") groupId: string, @MessageBody("userIds") userIds: string[], @ConnectedSocket() client: Socket) {
    if (debug) console.log(`DEBUG | chat.controller | addUserToGroup | userId: ${userIds}`);
    let userIdsList = userIds.map((userId) => {
      return Number(userId);
    });
    let isAdminId = this.jwtService.decode(client.handshake.auth.token)['sub'];

    this.chatService.addUsersToGroup(Number(groupId), userIdsList, Number(isAdminId)).then((res) => {
      let otherMembers = res.subscriptions;
      if (!otherMembers)
        return { response: true };
      otherMembers.forEach((memberId) => {
        let recClientId = this.clients.get(Number(memberId.player.id));
        let newUsers = otherMembers.filter((otherMember) => {
          return userIdsList.includes(otherMember.player.id);
        });
        if (recClientId)
          this.server.to(`${recClientId.id}`).emit('addusertogroup', { groupId, newUsers });
        return { response: true };
      });
      for (let userId of userIdsList) {
        let recClientId = this.clients.get(Number(userId));
        if (recClientId)
          this.server.to(`${recClientId.id}`).emit('newparent', { id: groupId, name: res.name, lastMessage: res.messages[0]?.createdAt, isGroup: true });
      }
      return { response: true };
    });
    return { response: true };
  }

  @SubscribeMessage("removemefromgroup")
  removeMeFromGroup(@MessageBody("groupId") groupId: string, @ConnectedSocket() client: Socket) {
    let me = this.jwtService.decode(client.handshake.auth.token)['sub'];
    let recClientId: Socket;
    if (!me)
      return { success: false };
    return this.chatService.removeUserFromGroup(Number(me), Number(groupId), Number(me)).then((otherMembers) => {
      if (debug) console.log(`DEBUG | chat.controller | removeMeFromGroup | otherMembers: ${otherMembers}`);
      if (otherMembers[0] === "bad request")
        return { success: false };
      if (otherMembers[0] === "delete group")
        return { success: true };
      if (!otherMembers)
        return { success: false };
      otherMembers.forEach((memberId) => {
        recClientId = this.clients.get(Number(memberId.playerID));
        if (debug) console.log(`DEBUG | chat.controller | removeMeFromGroup | memberId: ${recClientId}`);
        if (recClientId)
          this.server.to(`${recClientId.id}`).emit('removeuserfromgroup', { userId: me, groupId });
        return { success: true };
      });
      recClientId = this.clients.get(Number(me));
      if (recClientId)
        this.server.to(`${recClientId.id}`).emit('removeparent', { id: groupId });
      return { success: true };
    });
  }


  @SubscribeMessage("removeuserfromgroup")
  removeUserFromGroup(@MessageBody("userId") userId: string, @MessageBody("groupId") groupId: string, @ConnectedSocket() client: Socket) {
    let adminId = this.jwtService.decode(client.handshake.auth.token)['sub'];
    this.chatService.removeUserFromGroup(Number(userId), Number(groupId), Number(adminId)).then((otherMembers) => {
      if (debug) console.log(`DEBUG | chat.controller | removeUserFromGroup | otherMembers: ${otherMembers}`);
      if (otherMembers[0] === "bad request")
        return { success: false };
      if (otherMembers[0] === "delete group")
        return { success: true };
      otherMembers.forEach((memberId) => {
        let recClientId = this.clients.get(Number(memberId.playerID));
        if (debug) console.log(`DEBUG | chat.controller | removeUserFromGroup | memberId: ${recClientId}`);
        if (recClientId)
          this.server.to(`${recClientId.id}`).emit('removeuserfromgroup', { userId, groupId });
        return { success: true };
      }
      )
      return { success: true };
    });
    return { success: true };

  }

  @SubscribeMessage("creategroupchat")
  @UsePipes(new ValidationPipe())
  createGroupChat(@MessageBody("group") group: CreateGroupDto) {
    if (debug) console.log(`DEBUG | chat.controller | createGroupChat | group: ${group}`);
    this.chatService.createGroupChat(group).then((newparent) => {
      let id = newparent.groupID;
      let name = newparent.name;
      let lastMessage = newparent.createdAt;
      let isGroup = true;

      group.members.forEach((memberId) => {
        let recClientId = this.clients.get(Number(memberId));
        if (recClientId)
          this.server.to(`${recClientId.id}`).emit('newparent', { id, name, lastMessage, isGroup });
      });
    });
  }

  @SubscribeMessage('message')
  @UsePipes(new ValidationPipe())
  async handleMessage(@MessageBody() createChatDto: CreateChatDto, @ConnectedSocket() client: Socket) {
    if (debug) console.log(`DEBUG | chat.gateway | handleMessage | data: ${createChatDto.content}, ${createChatDto.receiverID}, ${createChatDto.senderID}, ${createChatDto.receiversID}`);
    let recClientId: Socket;

    let senderID = this.jwtService.decode(client.handshake.auth.token)['sub']
    let resIds = await this.chatService.create(createChatDto, Number(senderID));
    let blocked_users = await this.chatService.getBlockedUsers(Number(senderID));
    console.log("resIds", resIds);
    if (resIds == "isMuted")
      return { success: false };
    if (resIds.length == 0)
      return { success: true };
    if (!resIds)
      return { success: false };
    if (resIds[0] == null)
      return { success: false };

    if (debug) console.log(`DEBUG | chat.gateway | handleMessage | resIds: ${resIds}`);
    for (let resId of resIds) {
      if (blocked_users.includes(resId.playerID))
        createChatDto.content = "This message is blocked";
      recClientId = this.clients.get(Number(resId.playerID));
      let data = JSON.stringify({ data: JSON.stringify({ ...createChatDto, "senderName": resId.senderName }) });
      if (recClientId)
        this.server.to(`${recClientId.id}`).emit('message', data);
    }
    return { success: true };
  }

  @SubscribeMessage("searchgroups")
  searchGroups(@MessageBody("groupSearch") groupSearch: string, @ConnectedSocket() client: Socket) {
    if (debug) console.log(`DEBUG | chat.controller | searchGroups | groupSearch: ${groupSearch}`);
    let userId = this.jwtService.decode(client.handshake.auth.token)['sub'];
    return this.chatService.searchGroups(groupSearch, Number(userId));
  }

  @SubscribeMessage("joingroup")
  async joinGroup(@MessageBody("groupId") groupId: string, @MessageBody("password") password: string, @ConnectedSocket() client: Socket) {
    if (debug) console.log(`DEBUG | chat.controller | joinGroup | groupId: ${groupId}`);
    let userId = this.jwtService.decode(client.handshake.auth.token)['sub'];
    let res = await this.chatService.joinGroup(Number(groupId), Number(userId), password);
    if (!res)
      return { error: "wrong password" };
    let recClientId = this.clients.get(Number(userId));
    if (debug) console.log(`DEBUG | chat.controller | joinGroup | memberId: ${recClientId}`);
    if (recClientId)
      this.server.to(`${recClientId.id}`).emit('newparent', { id: groupId, name: res.name, lastMessage: res.messages[0]?.createdAt, isGroup: true });
  }

  @SubscribeMessage("editGroup")
  @UsePipes(new ValidationPipe())
  async editGroup(@MessageBody("group") group: UpdateGroupDto, @ConnectedSocket() client: Socket) {
    // console.log(`DEBUG | chat.controller | editGroup | group: ${group}`);
    let userId = this.jwtService.decode(client.handshake.auth.token)['sub'];
    let res = await this.chatService.editGroup(group, Number(userId));
    if (!res)
      return { error: "not admin" };
    return { success: true };
    // let recClientId = this.clients.get(Number(userId));
    // if (recClientId)
    //   this.server.to(`${recClientId.id}`).emit('editgroup', { id: group.id, name: group.name});
  }
}
