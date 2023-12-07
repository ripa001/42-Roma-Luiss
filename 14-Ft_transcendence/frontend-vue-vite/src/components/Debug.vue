<script lang="ts">
import { usePlayerStore, type Player, type Invite } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

const playerStore = usePlayerStore()
const { user, currentGame } = storeToRefs(playerStore)
const debug = false

export default {
	data() {
		return {
		}
	},
	computed: {
		host() : Player {
			return currentGame.value.host
		},
		guest() : Player {
			return currentGame.value.guest
		},
		gameInfo() : {hostID: number, guestID: number, watcher: boolean} {
			return currentGame.value.gameInfo
		},
		pitch_color() : string {
			return currentGame.value.customizations.pitch_color
		},
		paddle_color() : string {
			return currentGame.value.customizations.paddle_color
		},
		ball_color() : string {
			return currentGame.value.customizations.ball_color
		},
		status(): 'undefined' | 'building' | 'playing' | 'end'{
			return currentGame.value.status
		},
		waiting() : 'undefined'  | 'matchmaking' | 'invite' | 'streaming' | 'customization' | 'playing' {
			return currentGame.value.waiting
		},
		invite() : Invite{
			return currentGame.value.invite
		},
		streaming() : boolean {
			return (currentGame.value.status == 'playing' && currentGame.value.gameInfo.watcher == true)
		},
		endReason() : 'undefined' | 'hostWin' | 'guestWin' | 'userLeft' | 'aPlayerLeft' | 'opponentLeft' {
			return currentGame.value.endReason
		},
		finalScore() : { host : number, guest : number} {
			return currentGame.value.finalScore
		},
	},
	methods : {
		updateWaiting(value : 'undefined'  | 'matchmaking' | 'invite' | 'streaming' | 'customization' | 'playing'){
			playerStore.updateWaitingTesting(value)
		},
		updateStatus(value : 'undefined' | 'building' | 'playing' | 'end'){
			playerStore.updateStatusTesting(value)
		},
		updateInvite(value : boolean){
			playerStore.updateInviteTesting(value)
		}
	},

}
</script>

<template>
	<v-app-bar
		location="bottom"
		height="500"
		class="NavSideBar rounded ma-2"
		>
		<v-card
			style="display: flex; flex-direction: row; flex-wrap: wrap; align-content: stretch;"
			flat
		>
			<v-card style="display: flex; flex-direction: column; height: fit-content; " class="ma-2 pa-2">
				<p style="color: purple;">status = {{ status }} </p>
				<v-btn border @click="updateStatus('undefined')">undefined</v-btn>
				<v-btn border @click="updateStatus('building')">building</v-btn>
				<v-btn border @click="updateStatus('playing')">playing</v-btn>
				<v-btn border @click="updateStatus('end')">end</v-btn>
			</v-card>

			<v-card style="display: flex; flex-direction: column; height: fit-content;" class="ma-2 pa-2">
				<p style="color: purple;">waiting = {{ waiting }}</p>
				<v-btn border @click="updateWaiting('undefined')">undefined</v-btn>
				<v-btn border @click="updateWaiting('matchmaking')">matchmaking</v-btn>
				<v-btn border @click="updateWaiting('invite')">invite</v-btn>
				<v-btn border @click="updateWaiting('customization')">customization</v-btn>
				<v-btn border @click="updateWaiting('playing')">playing</v-btn>
			</v-card>

			<v-card style="display: flex; flex-direction: column; height: fit-content;" class="ma-2 pa-2">
				<p style="color: purple;">| Received |</p>
				<p style="color: purple;">{{ invite.received }}</p>
				<p style="color: purple;">{{ invite.senderID }}</p>
				<p style="color: purple;">{{ invite.senderUsername }}</p>
				<p style="color: purple;">| Sent |</p>
				<p style="color: purple;">{{ invite.sent }}</p>
				<p style="color: purple;">{{ invite.recipientID }}</p>
				<p style="color: purple;">{{ invite.recipientUsername }}</p>
			</v-card>	


			<v-card style="display: flex; flex-direction: column; height: fit-content;" class="ma-2 pa-2">
				<p style="color: purple;">gameInfo.host = {{ gameInfo.hostID }}</p>
				<p style="color: purple;">gameInfo.guestID = {{ gameInfo.guestID }}</p>
				<p style="color: purple;">gameInfo.watcher = {{ gameInfo.watcher }}</p>
			</v-card>



					
			<v-card style="display: flex; flex-direction: column; height: fit-content; " class="ma-2 pa-2">
				<p style="color: purple;">endReason = {{ endReason }}</p>
				<p style="color: purple;">finalScore = {{ finalScore }}</p>
			</v-card>

			<v-card style="display: flex; flex-direction: column; height: fit-content;" class="ma-2 pa-2">
				<p style="color: purple;">streaming = {{ streaming }}</p>
			</v-card>


			<v-card style="display: flex; flex-direction: column; height: fit-content;" class="ma-2 pa-2">
				<p style="color: purple;">customizations</p>
				<p style="color: purple;">ball_color = {{ ball_color }}</p>
				<p style="color: purple;">pitch_color = {{ pitch_color }}</p>
				<p style="color: purple;">paddle_color = {{ paddle_color }}</p>
			</v-card>	

		</v-card>
	</v-app-bar>
</template>
