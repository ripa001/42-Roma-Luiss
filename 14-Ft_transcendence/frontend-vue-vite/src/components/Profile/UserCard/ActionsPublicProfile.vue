<script lang="ts">
import { usePlayerStore, PlayerStatus, type Player } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

const playerStore = usePlayerStore()
const { user, friends, publicUsers } = storeToRefs(playerStore)
const debug = false

export default {
	props: {
		userProfile: {
			type: Object as () => Player,
			required: true
		},
	},
    data () {
        return {
			loading: false,
        }
    },
	watch: {},
	computed: {
		pending() : boolean {
			if (this.userProfile != undefined) 
				return -1 == publicUsers.value.findIndex(
					(usr: Player) => this.userProfile?.id == usr.id
				);
			return false
		}
	},
    methods: {
		toggleFriendshipRequest(){
			if (this.userProfile !=  undefined){
				if (debug) console.log(`addAsFriend: userProfile.id = ${this.userProfile?.id}, typeof is: ${typeof this.userProfile?.id}`)

				if (this.pending)
					playerStore.sendFriendshipRejection(Number(this.userProfile?.id));
				else
					playerStore.sendFriendshipRequest(Number(this.userProfile?.id));				
			}
		},
		blockUser(){
			if (this.userProfile !=  undefined)
				playerStore.toggleBlockUser(this.userProfile?.id, true)
		},
	},
    mounted (){
    },
}
</script>

<template>
	<v-card
		v-if="userProfile != undefined"
		class="itemActions itemActionsPublicProfile"
		density="compact"
		variant="flat"
	>
		<v-btn
			v-if="!pending"
			@click="toggleFriendshipRequest"
			text="Send Friendship Request"
			prepend-icon="mdi-account-plus"
			color="white"
			block
		></v-btn>

		<v-btn
			v-if="pending"
			@click="toggleFriendshipRequest"
			text="Cancel Friendship Request"
			prepend-icon="mdi-account-remove"
			color="purple-lighten-4'"
			block
		></v-btn>		

		<v-btn
			:text="'Block ' + `${userProfile?.username}`"
			@click="blockUser"
			prepend-icon="mdi-account-cancel"
			block
		></v-btn>
	</v-card>
</template>

<style>
.itemActions {
	display: flex;
	flex-direction: column;
	margin: 1%;
	padding: 1%;
	/* background-color: rgb(13, 114, 78); */
	background-color: transparent;
}

.backgroundItem {
	background-color: rgba(255, 255, 255, 0.497);
	color: black;
	border-radius: 30px; /*Increase or decrease the value for controlling the roundness*/
	width: fit-content;
}

</style>