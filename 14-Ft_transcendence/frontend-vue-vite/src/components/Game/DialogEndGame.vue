<script lang="ts">
import { defineComponent } from 'vue'
import { usePlayerStore } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

const playerStore = usePlayerStore()
const { user, currentGame } = storeToRefs(playerStore)
const debug = false

export default defineComponent({
	computed : {
		dialogBox(){
			if (debug) console.log('| DialogEnd | computed | dialogBox : ' + (currentGame.value.status == 'end'))
			return (currentGame.value.status == 'end')
		},
		title() : string {
			if (debug) console.log('| DialogEnd | computed | title')
			switch(currentGame.value.endReason){
					case 'hostWin'	: return (this.userIsHost == true ? 'You have won !' : this.userisWatcher == true ? 'Host has won' : 'You have lost ...')
					case 'guestWin'	: return (this.userIsGuest == true ? 'You have won !' : this.userisWatcher == true ? 'Host has won' : 'You have lost ...')
					case 'userLeft'	: return 'You have left the game'
					case 'aPlayerLeft': return 'A player left the game'
					case 'opponentLeft' : return 'Your opponent left the game'
					default: // if 'undefined'
					return ''
				}
		},
		someoneWon() : boolean {
			if (debug) console.log('| DialogEnd | computed | someoneWon : ' + (currentGame.value.endReason == 'hostWin' || currentGame.value.endReason == 'guestWin'))
			return (currentGame.value.endReason == 'hostWin' || currentGame.value.endReason == 'guestWin')
		},
		userIsHost() : boolean {
			if (debug) console.log('| DialogEnd | computed | userIsHost : ' + (currentGame.value.host.id == user.value.id))
			return (currentGame.value.host.id == user.value.id)
		},
		userIsGuest() : boolean {
			if (debug) console.log('| DialogEnd | computed | userIsGuest : ' + (currentGame.value.guest.id == user.value.id))
			return (currentGame.value.guest.id == user.value.id)
		},
		userisWatcher() : boolean {
			if (debug) console.log('| DialogEnd | computed | userIsGuest : ' + (currentGame.value.guest.id == user.value.id))
			return (currentGame.value.gameInfo.watcher == true)
		},
		score() : { host : number, guest : number} {
			if (debug) console.log('| DialogEnd | computed | score : ' + currentGame.value.finalScore.host + ' | ' +  currentGame.value.finalScore.guest)
			return {
				host: currentGame.value.finalScore.host,
				guest: currentGame.value.finalScore.guest
			};
		},
		hostName() : string {
			if (debug) console.log('| DialogEnd | computed | hostName : ' + currentGame.value.host.username)
			return currentGame.value.host.username
		},
		guestName() : string {
			if (debug) console.log('| DialogEnd | computed | guestName : ' + currentGame.value.guest.username)
			return currentGame.value.guest.username
		},
	},
	methods: {
		exit(){
			if (debug) console.log('| DialogEnd | methods | exit')
			playerStore.forceCanvasUnmount()
		},
	},
})
</script>

<template>
	<v-overlay
		:model-value="dialogBox"
		persistent
		class="align-center justify-center"
	>
		<v-card
			rounded
			class="dialog bg-white ma-auto pa-4"
		>
			<v-card-title class="text-button text-center">{{ title }}</v-card-title>

			<v-card
				v-if="someoneWon"
				class="justify-center ma-5"
				flat
				style="display: flex; flex-direction: row;"				
			>
				<v-card class="ma-1 pa-1 text-center" flat>
					<v-card-item title="Host" >
						<p>{{ hostName}}</p>
						<v-chip
							class="my-2 text-h6 font-weight-bold" variant="tonal"
							:color="score.host > score.guest ? 'success' : score.host === score.guest ? 'grey' : 'error'"
						>{{ score.host }}</v-chip>
					</v-card-item>					
				</v-card>

				<v-card class="ma-1 pa-1 text-center" flat>
					<v-card-item title="Guest">
						<p>{{ guestName}}</p>
						<v-chip
							class="my-2 text-h6 font-weight-bold" variant="tonal"
							:color="score.guest > score.host ? 'success' : score.guest === score.host ? 'grey' : 'error'"
						>{{ score.guest }}</v-chip>
					</v-card-item>
				</v-card>

			</v-card>

			<v-card-item class="text-center ma-2">
				<v-btn
					text="Exit"
					@click="exit"
					size="large"
					color="primary"
					variant="tonal"
				></v-btn>
			</v-card-item>
		</v-card>
	</v-overlay>
</template>
