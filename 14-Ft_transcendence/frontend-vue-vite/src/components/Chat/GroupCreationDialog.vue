<template>
	<v-dialog v-model="groupChatDialog" max-width="500">
	  <v-card>	
		<v-card-title>Enter Group Chat Name</v-card-title>
		<v-card-text>
		  <v-text-field v-model="group.name" label="Group Chat Name"></v-text-field>
		</v-card-text>
		<v-card-title>Select Friends for Group Chat</v-card-title>
			<v-select
				v-model="group.members"
				:items="friends"
				item-title="name"
				item-value="id"
				label="Select Item"
				multiple
			>
				<template v-slot:selection="{ item, index }">
				<v-chip>
					<span>{{ item.title }}</span>
				</v-chip>
				</template>
			</v-select>
			<v-card-title>Group privacy</v-card-title>
			<v-radio-group v-model="group.visibility" row>
				<v-radio label="Public" value="public"></v-radio>
				<v-radio label="Protected" value="protected"></v-radio>
				<v-radio label="Private" value="private"></v-radio>
			</v-radio-group>
			<v-card-title v-if="group.visibility === 'protected'">Group password</v-card-title>
			<v-text-field v-if="group.visibility === 'protected'" v-model="group.password" label="Group password"></v-text-field>
			<v-card-actions>
		  <v-btn @click="createGroupChatWithSelectedFriends">Create Group Chat</v-btn>
		  <v-btn @click="closeGroupChatPopup">Cancel</v-btn>
		</v-card-actions>
	  </v-card>
	</v-dialog>
  </template>
  
  <script>
  export default {
	data() {
		
	  return {
		groupChatDialog: false,
		friendSearch: '',
		friends: [], // Populate this with your list of friends from the backend
		socket: null,
		group: {
			name: '',
			founderId: 0,
			members: [],
			visibility: "",
			password: ''
		},
	  };
	},
	computed: {
	  filteredFriends() {
		return this.friends
	  },
	},
	methods: {
	  closeGroupChatPopup() {
		this.group.members = [];
		this.groupChatDialog = false;
		this.group.name = '';
		this.group.visibility = 'private';

	  },
	  createGroupChatWithSelectedFriends() {
		try {
				if (this.group.name == "")
					alert("Group name cannot be empty");
				else if (this.group.visibility == "protected" && (!this.group.password || this.group.password == ""))
					alert("Group password cannot be empty");
				else
				{
					this.group.members.push(this.group.founderId);
					this.socket.emit("creategroupchat", { group: this.group }, (response) => {
						console.log("response", response);
					});
				}
			} catch (error) {
				console.error("Error emitting 'getmessagesprivatechat':", error);
		}
		this.closeGroupChatPopup();
	  },
	},
  };
  </script>
  