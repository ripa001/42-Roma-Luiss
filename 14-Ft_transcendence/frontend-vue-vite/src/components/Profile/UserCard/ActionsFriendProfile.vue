<script lang="ts">
import { defineComponent } from 'vue'
import { usePlayerStore, type Player } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

const playerStore = usePlayerStore()
const { currentGame } = storeToRefs(playerStore)
const debug = false

export default defineComponent({
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
	computed : {
		inviteSent() : boolean {
			if (debug) console.log('| ActionsFRiendProfile | conputed | inviteSent()')
			return (currentGame.value.waiting == 'invite')
		}
	},	
	watch : {
	},
    methods: {
		removeFromFriends(){
			console.log('| ActionsFRiendProfile | methods | removeFromFriends()')
			if (this.userProfile != undefined)//! was MODIFIED acces with '?' operator
				playerStore.sendFriendshipRejection(this.userProfile.id);
		},
		blockUser(){
			if (debug) console.log('| ActionsFRiendProfile | methods | blockUser()')
			if (this.userProfile != undefined) 
				playerStore.toggleBlockUser(this.userProfile?.id, true)
		},
		sendInviteToPlay(){
			if (debug) console.log('| ActionsFRiendProfile | methods | sendInviteToPlay()')
			if (this.userProfile != undefined) 
				playerStore.sendInvitation(this.userProfile?.id)
		},
		streamUser(){
			if (debug) console.log('| ActionsFRiendProfile | methods | streamUser()')
			if (this.userProfile != undefined) 
				playerStore.sendStreamingRequest(this.userProfile?.id)
		},
	},
    mounted (){
    },
})
</script>

<template>
	<v-card
		v-if="userProfile != undefined"
		class="itemActions itemActionsFriendProfile"
		density="compact"
		variant="flat"
	>
		<v-btn
			v-if="`${userProfile?.status}` === 'online'"
			:text="'Play with ' + `${userProfile?.username}`"
			@click="sendInviteToPlay"
			prepend-icon="mdi-controller"
			:disabled="inviteSent"
			block
		></v-btn>
		<v-btn
			:text="'Chat with ' + `${userProfile?.username}`"
			to="/chat"
			prepend-icon="mdi-chat"
			block
		>
		</v-btn>
		<v-btn
			v-if="`${userProfile?.status}` === 'playing'"
			:text="'Watch ' + `${userProfile?.username}` + '\'s game'"
			@click="streamUser"
			prepend-icon="mdi-play"
			block
		>
		</v-btn>

		<v-btn
			:text="'Remove ' + `${userProfile?.username}`"
			@click="removeFromFriends"
			prepend-icon="mdi-account-remove"
			block
		></v-btn>

		<v-btn
			:text="'Block ' + `${userProfile?.username}`"
			@click="blockUser"
			prepend-icon="mdi-account-cancel"
			block
		>
		</v-btn>
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