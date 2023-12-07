<script lang="ts">
import Notifications from '@/components/Notifications.vue';
import NavSideBar from '../components/NavSideBar.vue'
import Leaderboard from '@/components/Game/Leaderboard.vue'
import AboutGame from '@/components/Game/AboutGame.vue';
import DialogEndGame from '@/components/Game/DialogEndGame.vue';
import CanvasGame from '@/components/Game/CanvasGame.vue';
import DialogWaiting from '@/components/Game/DialogWaiting.vue';
import DialogInvite from '@/components/Game/DialogInvite.vue';
import DialogCustomization from '@/components/Game/DialogCustomization.vue';
import Debug from '@/components/Debug.vue';

import { storeToRefs } from 'pinia'
import { usePlayerStore} from '@/stores/PlayerStore';
import LiveStream from '@/components/Game/LiveStream.vue';

const playerStore = usePlayerStore()
const { user, currentGame } = storeToRefs(playerStore)

const debug = false

export default {
	components : {
    NavSideBar,
    Notifications,
    AboutGame,
    Leaderboard,
    CanvasGame,
    DialogWaiting,
    DialogInvite,
    DialogCustomization,
    DialogEndGame,
    Debug,
    LiveStream
},
	data: () => ({
	}),
	computed: {
		status() : 'undefined' | 'building' | 'playing' | 'end' {
			if (debug) console.log('| GameView | computed | status : ' + currentGame.value.status)
			return currentGame.value.status
		},
		user() {
			if (debug) console.log('| GameView | computed | user')
			return user.value
		},
	},
	methods: {
		sendMatchMakingRequest(){
			playerStore.sendMatchMakingRequest()
		}
	},
	unmounted() {
		// which variables to reset
	},
}
</script>

<template>
    <div v-if="!user.locked">
	<NavSideBar />
	<Notifications/>
	<!-- <Debug></Debug> -->
	<AboutGame v-if="status == 'undefined'"></AboutGame>
	<DialogWaiting/>
	<DialogInvite/>
	<DialogCustomization/>
	<DialogEndGame/>

	<v-main>
		<v-card
			class="game flex-column backgroundGame"
		>

			<LiveStream
				v-if="status == 'undefined'"
			></LiveStream>

			<v-card-item 
				v-if="status == 'undefined'"
				class="ma-7"
			>
				<v-btn
					color="primary"
					variant="elevated"
					size="x-large"
					class="mx-3"
					@click="sendMatchMakingRequest"
					text="Play now !"
				></v-btn>
			</v-card-item>

			<Leaderboard
				v-if="status == 'undefined'"
			></Leaderboard>	


			<v-card-item
				v-if="status == 'building' || status == 'playing' || status == 'end' "
				class="text-center"
				style="font-weight: bolder; font-size:x-large;" prepend-icon="mdi-cat" append-icon="mdi-cat"
			>
				<h2>CAT PONG</h2>
			</v-card-item>

			<CanvasGame
				v-if="status == 'building' || status == 'playing' || status == 'end'"
			></CanvasGame>

		</v-card>
	</v-main>
	</div>
	<div v-else>
		WARNING : You can view one page at a time. Please close the other tabs. and reload this page. Page is locked: {{ user.locked }}
	</div>
</template>

<style scoped>
.game {
	background-color: antiquewhite;
	height: 100%;
	width: 100%;
	display: flex;
	justify-content: center;
	justify-items: center;
	align-content: center;
	align-items: center;

}
.backgroundGame {
    position: absolute;
    top: 0;
    left: 0;
    transform: scale(1.1);
    background: url(../../cats_ai.webp) no-repeat center center;
    /* background: url(../../catwar.png) no-repeat center center; */
    background-size: cover;
}

.component {
	background-color: white;
}
</style>

