<template>
	<div class="text-center">
	  <v-menu
		v-model="menu"
		:close-on-content-click="false"
		location="end"
	  >
		<template v-slot:activator="{ props }">
		  <v-btn
			color="indigo"
			v-bind="props"
		  >
			Edit user
		  </v-btn>
		</template>
  
		<v-card min-width="300">
		  <v-list>
			  <!-- use user info to show -->
			<v-list-item
			:title="userInfo.name"
			>
			  
			</v-list-item>
		  </v-list>
  
		  <v-divider></v-divider>
  
		  <v-list>
			<v-list-item>
			  <v-switch
				v-model="userInfo.isAdmin"
				color="green"
				label="Administrator"
				hide-details
			  ></v-switch>
			</v-list-item>
  
			<v-list-item>
			  <v-switch
				v-model="userInfo.isMuted"
				color="purple"
				label="Muted"
				hide-details
			  ></v-switch>
			</v-list-item>

			<v-list-item>
			  <v-switch
				v-model="userInfo.isBanned"
				color="red"
				label="Banned"
				hide-details
			  ></v-switch>
			</v-list-item>
		  </v-list>
  
		  <v-card-actions>
			<v-spacer></v-spacer>
			<v-btn @click="removeUser(userInfo.id)" color="secondary" class="mr-2" outlined>
				Remove user {{ userInfo.id }}
			</v-btn>
			<v-btn
			  variant="text"
			  @click="toggle"
			>
			  Cancel
			</v-btn>
			<v-btn
			  color="primary"
			  variant="text"
			  @click="save"
			>
			  Save
			</v-btn>
		  </v-card-actions>
		</v-card>
	  </v-menu>
	</div>
  </template>
  <script>
	
	export default {
		props: {
			userInfos: {
				type: Object,
				required: true,
			},
			socket: {
				type: Object,
				required: true,
			},
			groupId: {
				type: Number,
				required: true,
			},
		},
		data: () => ({
			menu: false,
			userInfo: {
				id: 0,
				name: '',
				imageUrl: '',
				isAdmin: false,
				isMuted: false,
				isBanned: false
			},
		}),
		created() {
			console.log("PopUpUserEdit created");
		},
		mounted() {
			this.userInfo = this.$props.userInfos;
		},
		methods: {
			toggle (event) {
				this.menu = !this.menu
				// console.log(event)
			},
			save() {
				this.$props.socket.emit("editusersubscription", { 
					"userId": this.userInfo.id,
					"groupId": this.$props.groupId,
					"isAdmin": this.userInfo.isAdmin,
					"isMuted": this.userInfo.isMuted,
					"isBanned": this.userInfo.isBanned,
				 }, (response) => {
					console.log("response", response);
					this.toggle();
				});
			},
			removeUser(id) {
				console.log("removing", id);
				this.$props.socket.emit("removeuserfromgroup", { 
					"userId": id,
					"groupId": this.$props.groupId,
				 }, (success) => {
					console.log("success", success);
					this.toggle();
				});
			},
	  },
	}
  </script>