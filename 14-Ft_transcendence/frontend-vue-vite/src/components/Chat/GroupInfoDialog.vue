<template>
	<v-dialog v-model="groupInfoDialog" max-width="600">
		<v-card>
			<div class="d-flex justify-space-between align-center pa-2 pointer elevation-1 mb-2">
				<v-card-title>{{ groupInfo.name }}</v-card-title>
			<div>
				<v-btn icon @click="editGroupPrivacy()" v-if="this.user.isAdmin" class="mr-2">
					<v-icon>mdi-pencil</v-icon>
				</v-btn>
				<v-btn icon @click="addusertogroup()" v-if="this.user.isAdmin">
					<v-icon>mdi-account-plus</v-icon>
				</v-btn>
			</div>
			</div>
			<v-card-text>
				<h3>Members</h3>
				<v-list dense>
					<div class="flex-1 mt-4 mb-4 overflow-y-auto fill-height max-height-400 px-4">
						<v-list-item v-for="(member, index) in groupInfo.members" :key="member.id">
							<v-list-item-title>{{ member.name }}</v-list-item-title>
							<div class="d-flex align-center">
								<v-list-item-subtitle v-if="member.isAdmin && member.name !== groupInfo.founder">Administrator</v-list-item-subtitle>
								<v-list-item-subtitle v-if="member.isAdmin && member.name === groupInfo.founder">Founder</v-list-item-subtitle>

								<v-list-item-subtitle v-if="member.isMuted">
									<v-icon>mdi-volume-off</v-icon>
								</v-list-item-subtitle>
								<v-list-item-subtitle v-if="member.isBanned">
									<v-icon>mdi-account-off</v-icon>
								</v-list-item-subtitle>

							</div>
							<v-list-item-action class="float-right">
								<PopUpUserEdit ref="select" :userInfos="member" :socket="socket" :groupId="groupInfo.id" v-if="this.user.isAdmin && member.id !== this.userId && member.name !== groupInfo.founder"/>
								<v-btn :to="{ name: 'profile', params: { id: (member.id) } }" color="secondary" class="mr-2" outlined>
									View Profile
								</v-btn>
							</v-list-item-action>
						</v-list-item>
					</div>
				</v-list>
			</v-card-text>
			<v-card-actions>
				<v-btn color="primary" @click="groupInfoDialog = false">Close</v-btn>
				<v-btn color="red" @click="leaveGroup" class="ml-2 float-right">Leave Group</v-btn>
			</v-card-actions>
		</v-card>
		<GroupAddUserDialog ref="groupAddUserDialog" :socketProp="this.socket" :groupId="this.groupInfo.id" :userId="userId"/>
		<GruopEditDialog ref="gruopEditDialog"/>
	</v-dialog>
</template>

<script>
import PopUpUserEdit from './PopUpUserEdit.vue';
import GroupAddUserDialog from './GroupAddUserDialog.vue';
import GruopEditDialog from './GruopEditDialog.vue';
export default {
	props: {
		socketProp: {
			type: Object,
			default: null,
		},
		userIdProp: {
			type: Number,
			default: 0,
		},
	},
	created() {
		this.socket = this.$props.socketProp;
		this.userId = this.$props.userIdProp
		this.socket.on("removeuserfromgroup", (data) => {
			if (data.success == false) {
				alert("You are not allowed to remove this user");
				this.$emit("reload");
			}
			console.log("removeuserfromgroup", data)
			if (data.groupId === this.groupInfo.id) {
				this.groupInfo.members = this.groupInfo.members.filter((member) => member.id !== data.userId);
				
			}
		});


		this.socket.on("addusertogroup", (data) => {
			if (data.groupId === this.groupInfo.id) {
				let users = data.newUsers.map((user) => {
					console.log("user", user);
					return {
						id: user.player.id,
						name: user.player.username,
						imageUrl: user.player.avatar,
						isAdmin: false,
						isMuted: false,
					};
				});
				this.groupInfo.members = [...this.groupInfo.members, ...users];
			}
		});
		

		this.socket.on("editusersubscription", (data) => {
			if (data.groupId === this.groupInfo.id) {
				console.log("editusersubscription", data);
				this.groupInfo.members = this.groupInfo.members.map((member) => {
					if (member.id === data.userId) {
						member.isMuted = data.isMuted;
						member.isAdmin = data.isAdmin;
					}
					if (data.userId === this.userId) {
						this.user.isMuted = data.isMuted;
						this.user.isAdmin = data.isAdmin;
					}
					return member;
				});
			}
		});
	},
	components: {
		PopUpUserEdit,
		GroupAddUserDialog,
		GruopEditDialog
	},
	data() {
		return {
			groupInfoDialog: false,
			toggleSelect: false,
			socket: null,
			userId: 0,
			user: {},
			groupInfo: {
				id: 0,
				name: '',
				imageUrl: '',
				founder: '',
				visibility: '',
				members: [],
				founder: '',
			},
		};
	},
	computed: {
		groupImage() {
			return this.groupInfo.groupImage;
		},
		groupMembers() {
			return this.groupInfo.groupMembers;
		},
	},
	methods: {
		editProfile() {
			this.$refs.select.onClick((e) => {
				console.log(e);
			});
		},
		addusertogroup() {
			this.$refs.groupAddUserDialog.groupAddUserDialog = true;
			this.socket.emit("getfriendsnotingroup", { userId: this.userId, groupId: this.groupInfo.id }, (response) => {
				this.$refs.groupAddUserDialog.friends = response.friends;
			});
		},
		leaveGroup() {
			this.socket.emit("removemefromgroup", { groupId: this.groupInfo.id }, (response) => {
				// console.log("response removemefromgroup", response);
				if (response.success == false)
					alert("You not allowed to leave this group");
				// waits(50);
				console.log("response removemefromgroup", response);
				this.$emit("reload");
				this.groupInfoDialog = false;
			});
		},
		editGroupPrivacy() {
			this.$refs.gruopEditDialog.groupChatDialog = true;
			this.$refs.gruopEditDialog.group = this.groupInfo;
			this.$refs.gruopEditDialog.socket = this.socket;
			
		},

		closeGroupChatPopup() {
			this.groupInfoDialog = false;
		},
	},
};
</script>
  
<style scoped>
.group-image {
	width: 100%;
	max-height: 200px;
	object-fit: cover;
}
</style>