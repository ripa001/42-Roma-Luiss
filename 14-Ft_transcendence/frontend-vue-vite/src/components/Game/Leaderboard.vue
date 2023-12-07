<script lang="ts">
import { usePlayerStore, type Player } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'
// import { VDataTableServer } from 'vuetify/labs/components'
import { VCardText } from 'vuetify/components'
import axios from 'axios'

const playerStore = usePlayerStore()
const { fetchAvatar } = storeToRefs(playerStore)

const _items_per_page = 5
const debug = false

export interface Entry {
	id: number,
	username: string,
	avatar: string,
	ladder_lvl: number,
	wins: number,
	losses: number,
}

export default {
	components:	{
		// VDataTableServer,
		VCardText

},
	data: () => ({
		showCustomization: false,
		loading: false,
		itemsPerPage: _items_per_page,
		totalItems: 0,
		board : [] as Entry[],
		headers: [
			{ title: 'Rank',align: 'center' },
			{ title: 'Player', key: 'username', align: 'center' },
			{ title: 'Ladder Level', key: 'ladder_lvl', align: 'center' },
			{ title: 'Victories', key: 'wins', align: 'center' },
			{ title: 'Losses', key: 'losses', align: 'center' }
		] as {title: string, key: string, align: 'start' | 'end' | 'center'}[],
	}),
	computed : {
	},
	watch : {
	},
	methods : {
		async fetchData(options: { page: number; itemsPerPage: number }) {
			if (debug) console.log('| Leaderboard | methods | fetchData() page:' + options.page + ' ipp: ' + options.itemsPerPage)
			this.loading = true
			const start = (options.page - 1) * options.itemsPerPage
			const end = start + options.itemsPerPage
			try {
				this.board = (await axios.get('players/leaderboard')).data

				// Filter out entries with zero wins and losses
				this.board = this.board.filter(entry => entry.wins > 0 || entry.losses > 0);

				// update avatar
				this.board.forEach(
					async (entry : Entry) => {
						entry.avatar = (await (fetchAvatar.value(entry.avatar)));
					})
				this.totalItems = this.board.length
				this.board = this.board.slice(start, end)
				this.loading = false
			} catch (err) {
				this.board = []
				this.totalItems = 0
				this.loading = false
				console.error(err)
			}
		},
	},


	beforeCreate() {
	if (debug) console.log('| Leaderboard | beforeCreate()')
	},
	created() {
		if (debug) console.log('| Leaderboard | created()')
	},
	beforeMount() {
		if (debug) console.log('| Leaderboard | beforeMount()')
		this.fetchData({page: 1 , itemsPerPage :  this.itemsPerPage})
	},
	mounted() {
		if (debug) console.log('| Leaderboard | mounted()')
	},
	beforeUpdate() {
		if (debug) console.log('| Leaderboard | beforeUpdate()')
	},
	updated() {
		if (debug) console.log('| Leaderboard | updated()')
	},
	beforeUnmount() {
		if (debug) console.log('| Leaderboard | beforeUnmount()')
	},
	unmounted() {
		if (debug) console.log('| Leaderboard | unmounted()')
	},
	}
</script>
  


<template>
	<v-card
		class="component justify-center align-center"	
		min-width="500"
	>
		<v-card-item density="compact">
			<v-card-subtitle class="text-overline text-center mb-3 pb-3">Leaderboard</v-card-subtitle>
		</v-card-item>
		<v-divider></v-divider>
		<v-data-table-server
			v-model:items-per-page="itemsPerPage"
			:items="board"
			:headers=headers
			:items-length="totalItems"
			:loading="loading"
			@update:options="fetchData"
			no-data-text="No one has played catPong yet, please come back later"
			density="compact"
			class="text-caption"
		>
			<template v-slot:item="{ item, index }">
				<tr>
					<td class="text-center">{{ index + 1 }}</td>
					<td class="text-caption justify-start ">
						<v-btn
							:to="{ name: 'profile', params: { id: item.id } }"
							variant="text" class="text-caption justify-start " block>
							<v-avatar :image="item.avatar" size="small" class="my-1 mr-3"></v-avatar>
							{{ item.username }}
						</v-btn></td>
					<td class="text-center">{{ item.ladder_lvl }}</td>
					<td class="text-center">{{ item.wins }}</td>
					<td class="text-center">{{ item.losses }}</td>
				</tr>
			</template>	
		</v-data-table-server>
	</v-card>
</template>

<style scoped>
.component {
	max-width:  100%;
	max-height:  100%;
	width: fit-content;
}

</style>


