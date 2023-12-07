<script lang="ts">
import { defineComponent } from 'vue'
import { usePlayerStore, CustomizationOptions, type Player } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

const playerStore = usePlayerStore()
const { user, currentGame } = storeToRefs(playerStore)
const debug = false

export default defineComponent({
	data() {
		return {
			customization : false,
			paddle_color: currentGame.value.customizations.paddle_color,
			ball_color: currentGame.value.customizations.ball_color,
			pitch_color: currentGame.value.customizations.pitch_color,
		}
	},
	computed : {
		dialogBox() : boolean {
			if (debug) console.log('| DialogCustomization | computed | dialogBox : ' + (currentGame.value.status == 'building' && currentGame.value.waiting == ''))
			return (currentGame.value.status == 'building' && currentGame.value.waiting == 'undefined' && currentGame.value.gameInfo.watcher == false)
		},
		opponentName() : string {
			if (debug) console.log('| DialogCustomization | computed | opponentName : ' + (user.value.id == currentGame.value.gameInfo.hostID ? currentGame.value.guest.username : user.value.id == currentGame.value.gameInfo.guestID ? currentGame.value.host.username :'N/A'))
			return user.value.id == currentGame.value.gameInfo.hostID ?
				currentGame.value.guest.username :
			user.value.id == currentGame.value.gameInfo.guestID ?
				currentGame.value.host.username :
			'N/A';
		},
		opponent() : Player {
			if (debug) console.log('| DialogCustomization | computed | opponent : ' + (user.value.id == currentGame.value.gameInfo.hostID ? currentGame.value.guest.username : user.value.id == currentGame.value.gameInfo.guestID ? currentGame.value.host.username :'N/A'))
			return user.value.id == currentGame.value.gameInfo.hostID ?
				currentGame.value.guest :
			user.value.id == currentGame.value.gameInfo.guestID ?
				currentGame.value.host :
			undefined;
		},
	},
	methods: {
		sendCustomization() {
			if (debug) console.log('| DialogCustomization | methods | sendCustomization : ')
			playerStore.sendCustomizationOptions({
				customization : this.customization,
				pitch_color: this.pitch_color,
				paddle_color: this.paddle_color,
				ball_color: this.ball_color,
			});
		},
	},
	watch: {
		dialogBox(isActive: boolean) {
			if (debug) console.log('| DialogCustomization | watcher | dialogBox : ' + isActive)
			if (isActive == false){
				this.customization = false
				this.paddle_color = '#800080';
				this.ball_color = '#800080';
				this.pitch_color = '#FFFFFF';	
			}
		},
		customization(isActive: boolean){
			if (isActive == false){
				this.paddle_color = '#800080';
				this.ball_color = '#800080';
				this.pitch_color = '#FFFFFF';				
			}
		},
	},
})
</script>

<template>
	<v-overlay
		:model-value="dialogBox"
		persistent
		class="align-center justify-center"
		min-width="1000"
	>
		<v-card rounded class="dialog bg-white ma-auto pa-4" flat>

			<v-card flat>
				<v-card-item class="justify-center  ma-5 text-center" style="font-weight: bolder; font-size: xx-large; flex-grow: 2;">
					<h1 class="text-h5 text-button">You are playing against</h1>
				</v-card-item>
				<v-card-item class="justify-center  ma-5 text-center" style="font-weight: bolder; font-size: x-large; flex-grow: 2;" :prepend-avatar="opponent?.avatar">
					<template v-slot:prepend><v-avatar size="x-large"></v-avatar></template>
					<h5 class="text-h5 text-button" style="font-weight: bolder;">{{  opponent?.username }}</h5>
				</v-card-item>
			</v-card>

			<v-card flat>
				<v-card-item>
					<p style="font-weight: bolder;">
						{{ customization? 'Your game is currently in customized mode' : 'Your game is currently in default mode' }}
					</p>
					<v-switch
						color="primary"
						:prepend-icon="customization? 'mdi-eraser' : 'mdi-brush'"
						:label="customization? 'set back to default' : 'customize'"
						v-model="customization"
						class="mx-1"
					></v-switch>
				</v-card-item>

				<v-card-item class="mb-3">
					<p>Customized settings features include :</p>
					<p>- points earned increase the size of your paddle</p>
					<p>- customized map colors</p>
				</v-card-item>
			</v-card>

			<v-card
				v-if="customization"
				class="justify-center align-center"
				flat
			>
				<v-card-item>
					<v-card-subtitle class="text-overline" style="font-weight: bolder;">
						Customize colors
					</v-card-subtitle>
				</v-card-item>

				<v-card
					style="display: flex; flex-direction: row; justify-content: space-around;"
					flat
				>
					<v-card-item class="ma-1 pa-1">
						<p class="text-overline">Paddles</p>
						<v-color-picker width="130" :modes="['hexa']" hide-inputs v-model="paddle_color"></v-color-picker>
						{{ paddle_color }}
					</v-card-item>
					<v-card-item class="ma-1 pa-1">
						<p class="text-overline">Pitch</p>
						<v-color-picker  width="130" :modes="['hexa']" hide-inputs v-model="pitch_color"></v-color-picker>
						{{ pitch_color }}
					</v-card-item>
					<v-card-item  class="ma-1 pa-1">
						<p class="text-overline">Ball</p>
						<v-color-picker  width="130" :modes="['hexa']" hide-inputs v-model="ball_color"></v-color-picker>
						{{ ball_color }}
					</v-card-item>
				</v-card>
			</v-card>

			<v-card flat>
				<v-card-item class="w-100 justify-center">
					<v-btn
						text="Send preferences"
						@click="sendCustomization"
						class="ma-4"
						color="primary"
						variant="elevated"
						size="large"
					></v-btn>
				</v-card-item>				
			</v-card>
		</v-card>
	</v-overlay>
</template>
