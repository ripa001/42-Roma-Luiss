<template>
	<!-- <div id="chat" class="flex-content"> -->
	<div id="chat">
		<v-app>
			<v-container class="fill-height pa-0" >
				<v-row class="no-gutters elevation-4" style="max-height: 50rem;">
					<v-col cols="12" sm="3" class="flex-grow-1 flex-shrink-0" style=" max-height: inherit;">
						<v-responsive class="" height="500">
							<v-list subheader >
								<v-btn @click="openGroupCreationPopup" style="margin-right: 5px;margin-bottom: 10px;">Create Group Chat</v-btn>
								<v-btn @click="openSearchGroupPopup" style="margin-bottom: 10px;">
									<v-icon>mdi-magnify</v-icon>
								</v-btn>
								<v-item-group v-model="this.activeChat" style="max-height: 27rem;" class="overflow-y-auto ">
									<template v-for="(item, index) in parents">
										<!-- {{ item.chatId }} -->
										<v-list-item :value="item.id" @click="activateChat(item.id, index, item.isGroup)" class="pa-4 pointer elevation-1 mb-2" >
											<v-avatar color="grey lighten-1 white--text" size="36" v-if="!item.isGroup && item.avatar" :image="item.avatar">
											</v-avatar>
											<v-avatar color="grey lighten-1 white--text" size="36" v-if="!item.isGroup && !item.avatar">
												<v-icon>mdi-account</v-icon>
											</v-avatar>
											<v-avatar color="grey lighten-1 white--text" size="36" v-if="item.isGroup">
												<v-icon>mdi-account-group</v-icon>
											</v-avatar>
											<v-list-item-title v-text="item.name" />
											<v-list-item-subtitle v-text="item.lastMessage" />
										</v-list-item>
										<v-divider class="my-0" />
									</template>
								</v-item-group>
							</v-list>
						</v-responsive>
					</v-col>
					<v-col cols="auto" class="flex-grow-1 flex-shrink-0">
						<v-responsive v-if="activeChat" class="overflow-y-hidden fill-height" height="500">
							<v-card flat class="d-flex flex-column fill-height">
								<div v-if="activeChat && !parents[activeChat - 1].isGroup" class="d-flex flex-row justify-space-between align-center pa-2 pointer elevation-1 mb-2" style="cursor: pointer;">

									<v-card-title>{{ parents[activeChat - 1].name }}</v-card-title>
									<v-spacer></v-spacer>
									<!-- add padding -->
									<v-btn @click="openInvitePopup(parents[activeChat - 1].id)" icon class="mr-2">
										<v-icon>mdi-controller</v-icon>
									</v-btn>
									<!-- <v-btn icon @click="viewUserProfile(parents[activeChat - 1].id)"> -->
									<v-btn icon :to="{ name: 'profile', params: { id: (parents[activeChat - 1].id) } }">
										...
									</v-btn>
								</div>
								<div v-if="activeChat && parents[activeChat - 1].isGroup" @click="openGroupInfoPopup()" class="d-flex flex-row justify-space-between align-center pa-2 pointer elevation-1 mb-2" style="cursor: pointer;">
									<v-card-title >{{ parents[activeChat - 1].name }}</v-card-title>
									<v-spacer></v-spacer>
									<v-btn icon>
										...
									</v-btn>
								</div>
								<!-- <v-card-title v-if="activeChat && parents[activeChat - 1].isGroup" @click="openGroupInfoPopup()">{{ parents[activeChat - 1].name }}</v-card-title> -->
								<v-card-text class="flex-grow-1 overflow-y-auto" style="max-height: 20rem;"> 	
									<template v-for="(msg, i) in messages" :key="`message${i}`">
										<div :class="{ 'd-flex flex-row-reverse': msg.me }">
											<v-menu offset-y>
												<template v-slot:activator="{ on }">
													<v-hover v-slot:default="{ hover }">
														<v-chip :color="msg.me ? 'primary': ''" dark
															style="height:auto;white-space: normal;" class="pa-4 mb-2">
															<p :color="'primary'">
																<b>{{ parents[activeChat - 1].isGroup ? (msg.me ? 'You' :
																	msg.senderName) : "" }}</b>
																<br>
																{{ msg.content }}
															</p>
															<sub class="ml-2" style="font-size: 0.5rem;">{{ msg.createdAt }}</sub>
															<v-icon v-if="hover" small>expand_more</v-icon>
														</v-chip>
													</v-hover>
												</template>
												<v-list>
													<v-list-item>
														<v-list-item-title>delete</v-list-item-title>
													</v-list-item>
												</v-list>
											</v-menu>
										</div>
									</template>
								</v-card-text>
								<v-card-text class="flex-shrink-1">
									<v-text-field v-model="messageForm.content" label="type_a_message" type="text"
										no-details outlined append-outer-icon="send" @keyup.enter="sendMessage"
										@click:append-outer="sendMessage" hide-details v-if="!this.isGroupActive || !this.$refs.groupInfoDialog.user.isMuted"/>
									
									<!-- show message "You are muted" -->
									<v-list-item v-if="this.isGroupActive && this.$refs.groupInfoDialog.user.isMuted" class="pa-4 pointer elevation-1 mb-2 bg-blue-grey lighten-5">
										<v-list-item-title>You are muted</v-list-item-title>
									</v-list-item>
									
								</v-card-text>
							</v-card>
						</v-responsive>
					</v-col>
				</v-row>
			</v-container>
		</v-app>
		<GroupSearchDialog ref="groupSearchDialog" />
		<GroupCreationDialog ref="groupCreationDialog" />
		<GroupInfoDialog ref="groupInfoDialog" :socketProp="this.socket" :userIdProp="this.userId" @reload="reloadData"/>
	</div>
</template>
  
<script>
import io from 'socket.io-client';
import { storeToRefs } from 'pinia'
import { usePlayerStore } from '@/stores/PlayerStore'
import axios from 'axios';
import { ref } from 'vue'
import GroupCreationDialog from './GroupCreationDialog.vue'
import GroupInfoDialog from './GroupInfoDialog.vue'
import GroupSearchDialog from './GroupSearchDialog.vue'

const playerStore = usePlayerStore()
const { user, friends } = storeToRefs(playerStore)

const showTime = (date) => {
	console.log("date", date);
	let d = new Date(date);
	let hours = d.getHours();
	let minutes = d.getMinutes();
	if (minutes < 10) {
		minutes = "0" + minutes;
	}
	let time = hours + ":" + minutes;
	return time;
};

export default {
	components: {
		GroupCreationDialog,
		GroupInfoDialog,
		GroupSearchDialog
		
	},
	data() {
		return {
			activeChat: 0,
			parents: [],
			friendsChat: [],
			groups: [],
			messages: [],
			userId: user.value.id,
			isGroupActive: false,
			messageForm: {
				content: "",
				me: true,
				senderID: user.value.id,
				receiverID: null,
				receiversID: null,
				createdAt: new Date()
			},
			socket: null,
			groupChatDialog: false,
			groupInfoDialog: false,
			groupChatName: '',

		};
	},
	computed: {
		avatar() {
			return async (avatar) => {
				return await this.fetchAvatar(avatar);
			};
		},
	},

	created() {
	
		try {
			if (!user.value.locked)
			{
				this.socket = io(`ws://${location.hostname}:${import.meta.env.VITE_BACKEND_PORT}/chat`, {
				transports: ['websocket'],
				auth: {
					'token': user.value.token
				}
			});
		}
			this.socket.emit("getparents", { userId: user.value.id }, (response) => {
				friends.value.forEach((friend) => {
					response.sortedData.forEach((parentResponse) => {
						if (friend.id == parentResponse.id) {
							parentResponse.avatar = friend.avatar;
						}
					});
					response.friends.forEach((friendResponse) => {
						if (friend.id == friendResponse.id) {
							friendResponse.avatar = friend.avatar;
						}
					});
				});

				this.parents = response.sortedData;
				this.friendsChat = response.friends;
				this.groups = response.rooms;
			});
		} catch (error) {
			console.error("Error emitting 'getmessagesprivatechat':", error);
		}
		

		this.socket.on("message", (message) => {
			console.log("parsedData", message);
			const parsedData = JSON.parse(JSON.parse(message).data);
			this.socket.emit("getparents", { userId: user.value.id }, (response) => {
				response.sortedData.forEach((parentResponse, index) => {
					if (this.activeChat && this.parents[this.activeChat - 1].id == parentResponse.id) {
						this.activeChat = index + 1;
					parentResponse.lastMessage = new Date(parentResponse.lastMessage).toLocaleString() ? parentResponse.lastMessage : "";
					}
				});
				friends.value.forEach((friend) => {
					response.sortedData.forEach((parentResponse, index) => {
						if (friend.id == parentResponse.id)
							parentResponse.avatar = friend.avatar;
					});
					response.friends.forEach((friendResponse) => {
						if (friend.id == friendResponse.id)
							friendResponse.avatar = friend.avatar;
					});
				});
				this.parents = response.sortedData;
				this.friendsChat = response.friends;
				this.groups = response.rooms;
			});
			if (parsedData.senderID == user.value.id)
				parsedData.me = true;
			else {
				parsedData.me = false;
				parsedData.createdAt = showTime(parsedData.createdAt);
				if (this.activeChat) {
					this.socket.emit("getmessages", { userId: user.value.id, chatId: this.parents[this.activeChat - 1].id, isGroup: this.parents[this.activeChat - 1].isGroup }, (response) => {
						let messages = response.messages;
						let subscriptions = response.subscriptions;
						console.log("messages", messages);
						if (response.isBlocked == true)
						{
							this.messages = []
							alert("You can't send message to this Chat 1")
							this.socket.emit("getparents", { userId: user.value.id }, (response) => {
								response.sortedData.forEach((parentResponse, index) => {
									if (this.activeChat && this.parents[this.activeChat - 1].id == parentResponse.id)
										this.activeChat = index + 1;
									parentResponse.lastMessage = new Date(parentResponse.lastMessage).toLocaleString();
								});
								friends.value.forEach((friend) => {
									response.sortedData.forEach((parentResponse) => {
										if (friend.id == parentResponse.id)
											parentResponse.avatar = friend.avatar;
									});
									response.friends.forEach((friendResponse) => {
										if (friend.id == friendResponse.id) {
											friendResponse.avatar = friend.avatar;
										}
									});
								});
								this.parents = response.sortedData;
								this.friendsChat = response.friends;
								this.groups = response.rooms;
								// console.log("this.activeChat", response.success);
								this.activeChat = 0;
							});
							return;
						}

						for (let i = 0; i < messages.length; i++) {
							if (messages[i].senderID == user.value.id)
								messages[i].me = true;
							else
								messages[i].me = false;
							messages[i].createdAt = showTime(messages[i].createdAt);
						}
						if (this.parents[this.activeChat -1 ].isGroup)
						{
							subscriptions.forEach((subscription) => {
								if (subscription.playerID == user.value.id) {
									this.$refs.groupInfoDialog.user.isAdmin = subscription.isAdmin;
									this.$refs.groupInfoDialog.user.isMuted = subscription.isMuted;
									this.$refs.groupInfoDialog.user.isBanned = subscription.isBanned;
								}
							});
						}
						this.messages = messages
					});
				}
			}
		});

		this.socket.on("newparent", (parent) => {
			this.parents.unshift(parent);
			if (this.activeChat)
				this.activeChat += 1;
		});

		this.socket.on("removeparent", (parent) => {
			this.parents.forEach((item, index) => {
				if (item.id == parent.id) {
					this.parents.splice(index, 1);
				}
			});
		});
	},
	
	mounted() {
		this.socket.emit("getparents", { userId: user.value.id }, (response) => {
			response.sortedData.forEach((parentResponse, index) => {
				parentResponse.lastMessage = new Date(parentResponse.lastMessage).toLocaleString();
			});
			friends.value.forEach((friend) => {
					response.sortedData.forEach((parentResponse) => {
						if (friend.id == parentResponse.id) {
							parentResponse.avatar = friend.avatar;
						}
					});
					response.friends.forEach((friendResponse) => {
						if (friend.id == friendResponse.id) {
							friendResponse.avatar = friend.avatar;
						}
					});
			});
			this.parents = response.sortedData;
			this.friendsChat = response.friends;
			this.groups = response.rooms;
		});
	},

	beforeUnmount() {
		this.activeChat = 0;
		this.messages = []
		// this.socket.disconn
	},
	beforeRouteLeave() {
		this.activeChat = 0;
		this.messages = []
	},
	methods: {
		
		sendMessage() {
			const newMessage = { ...this.messageForm };
			if (this.isGroupActive && this.$refs.groupInfoDialog.user.isMuted)
				return;
			newMessage.content = newMessage.content.trim();
			if (newMessage.content === "") return;
			if (newMessage.receiverID)
				newMessage.receiverID = this.parents[this.activeChat - 1].id;
			else if (newMessage.groupID)
				newMessage.receiversID = this.parents[this.activeChat - 1].id;
			newMessage.createdAt = new Date();
			// newMessage.content = 21;
			this.socket.emit("message", newMessage, (r) => {
				if (r.success == false) {
					this.messages = []
					this.activeChat = 0;
					alert("You can't send message to this Chat")
				}
				this.socket.emit("getparents", { userId: user.value.id }, (response) => {
					response.sortedData.every((parentResponse, index) => {
						if (this.activeChat && this.parents[this.activeChat - 1].id == parentResponse.id) {
							this.activeChat = index + 1;
							return false;
						}
						return true;
					});
					response.sortedData.forEach((parentResponse, index) => {
						parentResponse.lastMessage = new Date(parentResponse.lastMessage).toLocaleString();
					});

					friends.value.forEach((friend) => {
						response.sortedData.forEach((parentResponse) => {
							if (friend.id == parentResponse.id)
								parentResponse.avatar = friend.avatar;
						});
						response.friends.forEach((friendResponse) => {
							if (friend.id == friendResponse.id) {
								friendResponse.avatar = friend.avatar;
							}
						});
					});
					this.parents = response.sortedData;
					this.friendsChat = response.friends;
					this.groups = response.rooms;
					console.log("this.activeChat", r.success);
					// this.activeChat = r.success == true ? 1 : 0;
					console.log("this.activeChat", this.activeChat);
				});
				newMessage.createdAt = showTime(newMessage.createdAt);
				this.messages.push(newMessage);
				this.messageForm.content = "";
			});
		},

		openInvitePopup(id)
		{
			playerStore.sendInvitation(id);
		},

		reloadData() {
			console.log("reloadData");
			this.socket.emit("getparents", { userId: user.value.id }, (response) => {
				console.log("response", response);
				friends.value.forEach((friend) => {
					response.sortedData.forEach((parentResponse) => {
						if (friend.id == parentResponse.id) {
							parentResponse.avatar = friend.avatar;
						}
					});
					response.friends.forEach((friendResponse) => {
						if (friend.id == friendResponse.id) {
							friendResponse.avatar = friend.avatar;
						}
					});
				});
				this.activeChat = 0;
				this.parents = response.sortedData;
				this.friendsChat = response.friends;
				this.groups = response.rooms;
			});
		},

		activateChat(chatId, index, isGroup) {
			this.activeChat = index + 1;
			this.$refs.groupInfoDialog.user.isAdmin = false;
			this.$refs.groupInfoDialog.user.isMuted = false;
			this.$refs.groupInfoDialog.user.isBanned = false;
			this.isGroupActive = isGroup;
			this.fetchMessagesForChat(chatId, isGroup);
		},

		// viewUserProfile(userId) {
		// 	window.open(`http://${location.hostname}:8080/profile/${userId}`, '_blank');
		// },

		async fetchAvatarAsync(avatar) {
			try {
			const response = await axios.get(avatar, {
				responseType: 'arraybuffer',
			});
			const contentType = response.headers['content-type'];
			return `data:${contentType};base64,${Buffer.from(response.data, 'binary').toString('base64')}`;
			} catch (error) {
			console.log(`fetchAvatar() Exception: ${error}`);
			return '';
			}
		},

		fetchAvatar(avatar) {
			// Use a regular function that returns a Promise
			console.log("avatar", avatar);
			return this.fetchAvatarAsync(avatar);
		},

		// fetchAvatarAwait(avatar) {
		// 	// if (debug) console.log("/Store/ fetchAvatarAwait(" + avatar + ')');
		// 	return ref(this.fetchAvatar(avatar))
		// },

		async fetchMessagesForChat(chatId, isGroup) {
			let userId = user.value.id;
			this.messages = [];
			this.messageForm.receiverID = null;
			this.messageForm.receiversID = null;
			if (isGroup)
				this.messageForm.receiversID = chatId;
			else
				this.messageForm.receiverID = chatId;
			try {
				this.socket.emit("getmessages", { userId, chatId, isGroup }, (response) => {
					let messages = response.messages;
					let subscriptions = response.subscriptions;
					console.log("messages", response);
					if (response.isBlocked == true)
					{
						this.messages = []
						alert("You can't send message to this Chat 2")
						this.socket.emit("getparents", { userId: user.value.id }, (response) => {
							response.sortedData.forEach((parentResponse, index) => {
								if (this.activeChat && this.parents[this.activeChat - 1].id == parentResponse.id)
									this.activeChat = index + 1;
								parentResponse.lastMessage = new Date(parentResponse.lastMessage).toLocaleString();
							});
							friends.value.forEach((friend) => {
								response.sortedData.forEach((parentResponse) => {
									if (friend.id == parentResponse.id)
										parentResponse.avatar = friend.avatar;
								});
								response.friends.forEach((friendResponse) => {
									if (friend.id == friendResponse.id) {
										friendResponse.avatar = friend.avatar;
									}
								});
							});
							this.parents = response.sortedData;
							this.friendsChat = response.friends;
							this.groups = response.rooms;
							// console.log("this.activeChat", response.success);
							this.activeChat = 0;
						});
						return;
					}

					for (let i = 0; i < messages.length; i++) {
						if (messages[i].senderID == user.value.id)
							messages[i].me = true;
						else
							messages[i].me = false;
						messages[i].createdAt = showTime(messages[i].createdAt);
					}
					if (isGroup)
					{
						subscriptions.forEach((subscription) => {
							if (subscription.playerID == user.value.id) {
								this.$refs.groupInfoDialog.user.isAdmin = subscription.isAdmin;
								this.$refs.groupInfoDialog.user.isMuted = subscription.isMuted;
								this.$refs.groupInfoDialog.user.isBanned = subscription.isBanned;
							}
						});
					}
					this.messages = messages
				});
			} catch (error) {
				console.error("Error emitting 'getmessagesprivatechat':", error);
			}
		},

		openGroupCreationPopup() {
			this.messages = [];
			this.activeChat = 0;
			this.$refs.groupCreationDialog.groupChatDialog = true;
			this.$refs.groupCreationDialog.friends = this.friendsChat;
			this.$refs.groupCreationDialog.socket = this.socket;
			this.$refs.groupCreationDialog.group.founderId = user.value.id;
		},
		openSearchGroupPopup() {
			this.$refs.groupSearchDialog.dialog = true;
			this.$refs.groupSearchDialog.socket = this.socket;
			try {
				this.socket.emit("searchgroups", { groupSearch: this.groupSearch }, (response) => {
					this.$refs.groupSearchDialog.groups = response.groups;
				});
			} catch (error) {
				console.error("Error emitting 'searchgroups':", error);
			}
		},
		openGroupInfoPopup() {
			this.$refs.groupInfoDialog.groupInfoDialog = true;
			this.$refs.groupInfoDialog.user.isAdmin = false;
			this.$refs.groupInfoDialog.user.isMuted = false;
			this.$refs.groupInfoDialog.user.isBanned = false;
			this.socket.emit("getgroupinfo", { groupId: this.parents[this.activeChat - 1].id }, (response) => {
				if (response.error) {
					alert(response.error);
					return;
				}
				this.$refs.groupInfoDialog.groupInfo = response;
				
				for (let i = 0; i < response.members.length; i++) {
					if (response.members[i].id == user.value.id) {
						this.$refs.groupInfoDialog.user.isAdmin = response.members[i].isAdmin;
						this.$refs.groupInfoDialog.user.isMuted = response.members[i].isMuted;
						this.$refs.groupInfoDialog.user.isBanned = response.members[i].isBanned;
					}
				}
			});
		},

	},
};
</script>
  
<style scoped>


.v-list-item__subtitle {
	white-space: normal;
}

.v-list-item__title {
	white-space: normal;
}

#chat {
	/* all available screen */
	width: 100%;
	height: 100%;
	overflow-y: hidden;

	/* flexbox */
	display: flex;
	flex-direction: column;

    top: 0;
    left: 0;
    /* transform: scale(1.1); */
    /* background: url(../../catwar.png) no-repeat center center; */
    /* background: url(../../nyancat_bg.jpeg) no-repeat center center; */
    /* background: url(../../blackcat.jpeg) no-repeat center center; */
    /* background: url(../../blackcatspace.jpg) no-repeat center center; */
    /* background-size: cover; */
    /* position:absolute; */
	/* background-position: 100% 100%; */
}

</style>