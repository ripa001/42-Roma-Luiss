<script lang="ts">
import { defineComponent } from 'vue'
import { usePlayerStore } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

const playerStore = usePlayerStore()
const { currentGame } = storeToRefs(playerStore)
const debug = false

export default defineComponent({
	data() {
		return {
			isCancelActive:  false,
		}
	},
	computed : {
		dialogBox() : boolean{
			if (debug) console.log('| DialogInvite | computed | dialogBox : ' + currentGame.value.invite.received)
			return currentGame.value.invite.received
		},
		senderUsername() : string {
			if (debug) console.log('| DialogInvite | computed | HostName : ' + currentGame.value.invite.senderUsername)
			return currentGame.value.invite.senderUsername
		},
	},
	methods: {
		accept(){
			if (debug) console.log('| DialogInvite | methods | accept')
			playerStore.acceptInvitation();
			this.isCancelActive = true;
		},
		reject(){
			if (debug) console.log('| DialogInvite | methods | reject')
			playerStore.rejectInvitation();
			this.isCancelActive = true;
		},
	},
	watch: {
		isCancelActive(newVal : boolean){
			if (debug) console.log('| DialogInvite | watcher | isCancelActive : ' + newVal)
		},
		dialogBox(newVal : boolean){
			if (debug) console.log('| DialogInvite | watcher | dialogBox : ' + newVal)
			if (newVal == true)
				this.isCancelActive = false
		}
	},

})
</script>

<template>
	<v-overlay
		:model-value="dialogBox"
		persistent
		class="align-center justify-center"
	>
		<v-card rounded class="dialog bg-white ma-auto pa-4">
			
			<v-card-title class="text-button text-"> {{ senderUsername }} has invited you to a game !</v-card-title>
			
			<v-card
				class="text-center ma-2"
				flat
				style="display: flex; flex-direction: row; justify-content: center;"
			>
				<v-btn
					text="Accept" @click="accept" :disabled="isCancelActive"
					border color="primary" variant="elevated" class="ma-2 pa-2"
				></v-btn>
				<v-btn
					text="Decline" @click="reject" :disabled="isCancelActive"
					border color="primary" variant="elevated" class="ma-2 pa-2"
				></v-btn>
			</v-card>

		</v-card>
	</v-overlay>
</template>
