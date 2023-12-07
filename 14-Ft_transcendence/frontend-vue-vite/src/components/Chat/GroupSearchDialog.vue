<template>
	<v-dialog v-model="dialog" max-width="500">
	  <v-card>	
		<v-card-title>Enter Group Chat Name To Search</v-card-title>
		<v-card-text>
		  <v-text-field v-model="groupSearch" label="Group Chat Name" @input="searchGroups"></v-text-field>
		</v-card-text>
		<v-card-title>Search Result</v-card-title>
		<v-card-text>
			<v-list dense>
				<div class="flex-1 mt-4 mb-4 overflow-y-auto fill-height max-height-400 px-4">
					<v-list-item v-for="(group, index) in this.groups" :key="index">
						<v-list-item-title>{{ group.name }}</v-list-item-title>
						<v-list-item-subtitle v-if="group.visibility === 'public'">Public</v-list-item-subtitle>
						<v-list-item-subtitle v-if="group.visibility === 'protected'">Protected</v-list-item-subtitle>
						<v-list-item-action class="float-right">
							<v-text-field v-if="group.visibility === 'protected'" v-model="group.password" label="Password for protected groups" style="width: 200px; margin-top: 10px; padding-right: 10px;"></v-text-field>
							<v-btn color="primary" class="mr-2" outlined @click="joinGroup(group.groupID, group.password)">
								Join Group
							</v-btn>
						</v-list-item-action>
					</v-list-item>
				</div>
			</v-list>
		</v-card-text>

		<v-card-actions>
		  <v-btn @click="closeGroupChatPopup">Cancel</v-btn>
		</v-card-actions>
	  </v-card>
	</v-dialog>
  </template>
  
  <script>
  export default {
	data() {
		
	  return {
		dialog: false,
		groupSearch: '',
		groups: [], // Populate this with your list of groups from the backend
		socket: null,
		// group: {
		// 	name: '',
		// 	founderId: 0,
		// 	members: [],
		// 	visibility: "",
		// 	password: ''
		// },

	  };
	},
	computed: {
	  filteredFriends() {
		return this.friends
	  },
	  
	},
	methods: {
	  closeGroupChatPopup() {
		this.dialog = false;
		this.groupSearch = '';
		this.groups = [];
	  },

	  searchGroups() {
		try {
			this.socket.emit("searchgroups", { groupSearch: this.groupSearch }, (response) => {
				console.log("response search", response);
				this.groups = response.groups;
			});
		} catch (error) {
			console.error("Error emitting 'searchgroups':", error);
		}
	  },

	  joinGroup(groupId, password) {
		try {
			this.socket.emit("joingroup", { groupId: groupId, password: password }, (response) => {
				if (response.error) {
					alert(response.error);
				}
				// reload data
				// this.$emit('reload');
			});
			this.dialog = false;
			this.groupSearch = '';
			this.groups = [];
		} catch (error) {
			console.error("Error emitting 'joingroup':", error);
		}
	  },
	},
	
  };
  </script>
  