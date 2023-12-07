<template>
	<v-dialog v-model="groupAddUserDialog" max-width="500">
	  <v-card>
		<v-card-title>Select Friends to add</v-card-title>
			<v-select
				v-model="group.members"
				:items="friends"
				item-title="username"
				item-value="id"
				label="Select Item"
				multiple
			>
				<template v-slot:selection="{ item, index }">
				<v-chip>
					<span>{{ item.title }}</span>
				</v-chip>
				<!-- <span
					v-if="index === 2"
					class="text-grey text-caption align-self-center"
				>
					(+{{ value.length - 2 }} others)
				</span> -->
				</template>
			</v-select>
			<v-card-actions>
		  <v-btn @click="addUserToGroup">Add Users</v-btn>
		  <v-btn @click="closeGroupChatPopup">Cancel</v-btn>
		</v-card-actions>
	  </v-card>
	</v-dialog>
  </template>
  
  <script>
  export default {
	props: {
		socketProp: {
			type: Object,
			default: null,
		},
		groupId: {
			type: Number,
			default: 0,
		},
		userId: {
			type: Number,
			default: 0,
		},
	},
	data() {
		
	  return {
		groupAddUserDialog: false,
		friendSearch: '',
		friends: [], // Populate this with your list of friends from the backend
		socket: null,
		group: {
			name: '',
			founderId: 0,
			members: [],
			isPublic: false,
			password: ''
		},
	  };
	},
	created() {
		console.log("GroupAddUserDialog socket", this.$props.socketProp);
		this.socket = this.$props.socketProp;
		//   getFriendsNotInGroup(@MessageBody("userId") userId: string, @MessageBody("groupId") groupId: string) {
		console.log("this.$props.groupId", this.$props.groupId);
		// this.socket.emit("getfriendsnotingroup", { userId: this.$props.userId, groupId: this.$props.groupId }, (response) => {
		// 	console.log("response getfriendsnotingroup", response);
		// 	this.friends = response.friends;
		// });

		// this.socket.emit("getfriendsnotingroup", { userId: this.$props.userId }, (response) => {
		// 		this.friends = response.friends;
		// });
	},
	computed: {
	  filteredFriends() {
		return this.friends
	  },
	},
	methods: {

	  selectId(id) {
			console.log("id", id);
			this.group.members.push(id);
		},
	  closeGroupChatPopup() {
		this.group.members = [];
		this.groupAddUserDialog = false;
		this.group.name = '';

	  },
	  addUserToGroup() {
		try {
				// this.group.members.push(this.group.founderId);
				console.log("this.group.members", this.$props.groupId);
				// let strMembersIds = this.group.members.join(",");
				this.socket.emit("addusertogroup", { groupId: this.$props.groupId, userIds: this.group.members }, (response) => {
					console.log("response addtogroup", response);
					this.group.members = [];
					this.groupAddUserDialog = false;
					
				});
			} catch (error) {
				console.error("Error emitting 'getmessagesprivatechat':", error);
		}
	},
	},
  };
  </script>
  