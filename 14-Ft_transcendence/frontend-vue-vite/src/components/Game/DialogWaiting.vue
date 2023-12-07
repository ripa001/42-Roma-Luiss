<script lang="ts">
import { defineComponent } from 'vue'
import { usePlayerStore, type Player } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'
import { IntersectingCirclesSpinner } from 'epic-spinners'

const playerStore = usePlayerStore()
const { currentGame } = storeToRefs(playerStore)
const debug = false

export default defineComponent({
	components: {
    IntersectingCirclesSpinner,
	},
	data() {
		return {
			isCancelActive:  false,
		}
	},
	computed : {
		dialogBox() : boolean{
			if (debug) console.log('| DialogWaiting | computed | dialogBox : ' + (currentGame.value.waiting))
			return (currentGame.value.waiting != 'undefined')
		},
		buttonText() : string {
			if (debug) console.log('| DialogWaiting | computed | buttonText')
			switch(currentGame.value.waiting){
					case 'matchmaking'	: return 'cancel game request'
					case 'invite'		: return 'cancel invite'
					// case 'streaming'	: return 'cancel streaming request'
					case 'customization': return 'leave game'  
					case 'playing'		: return 'exit game' 
					default: // if 'undefined'
					return ''
				}
		},
		title() : string {
			if (debug) console.log('| DialogWaiting | computed | title')
			if (false == this.isCancelActive){
				switch(currentGame.value.waiting ){
					case 'matchmaking'	: return 'Searching for an opponent ...' 
					case 'invite'		: return 'Waiting for opponent ...'
					// case 'streaming'	: return 'Joining game ...' 
					case 'customization': return 'Waiting for opponent ...'  
					case 'playing'		: return 'Loading game ...'
					default: // if 'undefined'
					return ''
				}
			}
			else {
				switch(currentGame.value.waiting ){
					case 'matchmaking'	: return 'cancelling game request ...'
					case 'invite'		: return 'cancelling invite ...'
					// case 'streaming'	: return 'cancelling streaming request ...'
					case 'customization': return 'leaving game ...'  
					case 'playing'		: return 'exiting game ...' 
					default: // if 'undefined'
					return ''
				}				
			}
		},
	},
	methods: {
		buttonAction() {
			if (debug) console.log('| DialogWaiting | methods | buttonAction : ' + currentGame.value.waiting)
			if (this.dialogBox){
				switch(currentGame.value.waiting){
					case 'matchmaking'	: playerStore.cancelMatchMakingRequest();	break;
					case 'invite'		: playerStore.cancelInvitation();			break;
					// case 'streaming'	: playerStore.cancelStreamingRequest();		break;
					case 'customization': playerStore.exitGame();					break;
					case 'playing'		: playerStore.exitGame();					break;
					default: // if 'undefined'
						break;
				}
				this.isCancelActive = true;
			}
		},
	},
	watch: {
		isCancelActive(newVal : boolean){
			if (debug) console.log('| DialogWaiting | watcher | isCancelActive : ' + newVal)
		},
		dialogBox(newVal : boolean){
			this.isCancelActive = false
			if (debug) console.log('| DialogWaiting | watcher | dialogBox : ' + newVal)
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
		<v-card rounded class="dialog bg-white ma-auto pa-4 ">
			
			<v-card-title class="text-button text-center ">
				{{ title }}
			</v-card-title>
			
			<v-card-item
				class="justify-center ma-5 "
				v-show="isCancelActive == false"
			>
				<intersecting-circles-spinner :animation-duration="1200" :size="70" color="purple"/>
			</v-card-item>
			
			<v-card-item class="text-center ma-2 ">
				<v-btn
					:text="buttonText" @click="buttonAction" :disabled="isCancelActive"
					color="primary" variant="elevated"
				></v-btn>
			</v-card-item>

		</v-card>
	</v-overlay>
</template>
