<template>
	<v-dialog v-model="groupChatDialog" max-width="500">
	  <v-card>	
		<v-card-title>Group Chat Name</v-card-title>
		<v-card-text>
		  <v-text-field v-model="group.name" label="Group Chat Name"></v-text-field>
		</v-card-text>
		
			<v-card-title>Group privacy</v-card-title>
			<v-radio-group v-model="group.visibility" row>
				<v-radio label="Public" value="public"></v-radio>
				<v-radio label="Protected" value="protected"></v-radio>
				<v-radio label="Private" value="private"></v-radio>
			</v-radio-group>
			<v-card-title v-if="group.visibility === 'protected'">Group password</v-card-title>
			<v-text-field v-if="group.visibility === 'protected'" v-model="group.password" label="Group password"></v-text-field>
			<v-card-actions>
		  <v-btn @click="editGroup">Edit Group Chat</v-btn>
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
		socket: null,
		group: {
			id: 0,
			name: '',
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
		this.groupChatDialog = false;
	  },
	  editGroup() {
		try {
			console.log("group", this.group);
				if (this.group.name == "")
					alert("Group name cannot be empty");
				else if (this.group.visibility == "protected" && (!this.group.password || this.group.password == ""))
					alert("Group password cannot be empty");
				else
					this.socket.emit("editGroup", { group: this.group }, (response) => {
						if (response.success != true)
							alert("You are not allowed to edit this group");
					});
		} catch (error) {
				console.error("Error emitting 'edit group':", error);
		}
		this.closeGroupChatPopup();
	  },
	},
  };
  </script>
  