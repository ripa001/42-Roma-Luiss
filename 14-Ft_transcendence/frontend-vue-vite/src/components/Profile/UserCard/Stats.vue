<script lang="ts">
import { usePlayerStore, type Player, type Game } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

const playerStore = usePlayerStore()
const { fetchGames } = storeToRefs(playerStore)
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
			stats: {
				loading: false,
				victories: 0,
				losses: 0,
				ladder: 0
			},
        }
    },
    methods: {
		fetchStats() {
			if (debug) console.log('| Stats | methods | fetchStats()')
			if (this.userProfile != undefined) {
				this.stats.loading = true
				fetchGames.value(this.userProfile.id)
					.then((games : Game[]) => {
						this.stats.victories = this.stats.losses = this.stats.ladder = 0
						for (const game of games) {
							if (game.host == this.userProfile.username) {
								if (game.host_score > game.guest_score) this.stats.victories++
								else if (game.host_score < game.guest_score) this.stats.losses++
							} else {
								if (game.host_score > game.guest_score) this.stats.losses++
								else if (game.host_score < game.guest_score) this.stats.victories++
							}
							this.stats.ladder = Math.round(games.length * this.stats.victories / (this.stats.losses + 1))
						}
						this.stats.loading = false
					})
					.catch((err : Error) => {
						console.error(err)
						this.stats.loading = false
					})			
			}
		}
	},
	watch: {
		userProfile(newValue : Player){
			if (debug) console.log('| Stats | watch | userProfile : new value : ' + newValue.username)
			if (this.userProfile != undefined)
				this.fetchStats()
		},
	},
	beforeCreate() {
		if (debug) console.log('| Stats | beforeCreate()')
	},
	created() {
		if (debug) console.log('| Stats | created(' + (this.userProfile?.id) + ')')
	},
	beforeMount() {
		if (debug) console.log('| Stats | beforeMount(' + (this.userProfile?.id) + ')')
	},
	mounted() {
		if (debug) console.log('| Stats | mounted(' + (this.userProfile?.id) + ')')
		this.fetchStats();
    },
	beforeUpdate() {
		if (debug) console.log('| Stats | beforeUpdate(' + (this.userProfile?.id) + ')')
	},
	updated() {
		if (debug) console.log('| Stats | updated(' + (this.userProfile?.id) + ')')
	},
	beforeUnmount() {
		if (debug) console.log('| Stats | beforeUnmount(' + (this.userProfile?.id) + ')')
	},
	unmounted() {
		if (debug) console.log('| Stats | unmounted(' + (this.userProfile?.id) + ')')
	},
}
</script>

<template>
	<v-card
		class="itemStats backgroundItem"
		density="compact"
		variant="flat"
		:loading="stats.loading"
	>
		<v-card-title class="text-overline">Stats</v-card-title>
		<v-card-item
			prepend-icon="mdi-trophy"
			:title="String(stats.victories)"
			subtitle="victories"
		>
		</v-card-item>

		<v-card-item
			class=""
			prepend-icon="mdi-trophy-broken"
			:title="String(stats.losses)"
			subtitle="losses"
		>
		</v-card-item>

		<v-card-item
			class=""
			prepend-icon="mdi-sword-cross"
			:title="String(stats.ladder)"
			subtitle="ladder lvl"
		>
		</v-card-item>
	</v-card>
</template>

<style>

.itemStats {
	display: flex;
	flex-direction: column;
	margin: 1%;
	padding: 1%;
	background-color: transparent;
}

.backgroundItem {
	background-color: rgba(255, 255, 255, 0.497);
	color: black;
	border-radius: 30px; /*Increase or decrease the value for controlling the roundness*/
	width: fit-content;
}

</style>