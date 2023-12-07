<script lang="ts">
import { usePlayerStore, type Player, type ActiveGameDto } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'
import { VCardText } from 'vuetify/components'

const playerStore = usePlayerStore()
const { liveStreams } = storeToRefs(playerStore)

const _items_per_page = 5
const debug = false

export default {
	components:	{
		VCardText
	},

	data: () => ({
		showCustomization: false,
		loading: false,
		itemsPerPage: _items_per_page,
		totalItems: 0,
		list : liveStreams,
		headers: [
			{ title: 'Host', key: 'hostUsername', align: 'center' },
			{ title: 'Guest', key: 'guestUsername', align: 'center' },
			{ title: 'watch', key: 'watch', align: 'start' },
		] as {title: string, key: string, align: 'start' | 'end' | 'center'}[],
	}),
	created() {
		playerStore.sendGetActiveGames();
	},
	computed : {
	},
	watch : {
	},
	methods : {
		streamUser(id : number){
			if (debug) console.log('| LiveStream | methods | streamUser()')
			playerStore.sendStreamingRequest(id);
		},
		async fetchData(options: { page: number; itemsPerPage: number }) {
			if (debug) console.log('| LiveStream | methods | fetchData() page:' + options.page + ' ipp: ' + options.itemsPerPage)
			this.loading = true
			const start = (options.page - 1) * options.itemsPerPage
			const end = start + options.itemsPerPage
			this.list = liveStreams
			this.totalItems = this.list.length
			this.list = this.list.slice(start, end)
			this.loading = false
		},
	},

	}
</script>
  


<template>
	<v-card
		class="component justify-center align-center"	
		min-width="500"
	>
		<v-card-item density="compact">
			<v-card-subtitle class="text-overline text-center mb-3 pb-3">Now streaming</v-card-subtitle>
		</v-card-item>
		<v-divider></v-divider>
		<v-data-table-server
			v-model:items-per-page="itemsPerPage"
			:items="list"
			:headers=headers
			:items-length="totalItems"
			:loading="loading"
			@update:options="fetchData"
			no-data-text="there is no live game at the moment, please come back later"
			density="compact"
			class="text-caption"
		>
			<template v-slot:item="{ item }">
				<tr>
					<td class="text-caption justify-start text-center">
						<v-btn
							:to="{ name: 'profile', params: { id: item.hostID } }"
							variant="text" class="text-caption justify-start " block>
							<v-avatar :image="item.hostAvatar" size="small" class="my-1 mr-3"></v-avatar>
							{{ item.hostUsername }}
						</v-btn></td>
					<td class="text-caption justify-start text-center">
						<v-btn
							:to="{ name: 'profile', params: { id: item.guestID } }"
							variant="text" class="text-caption justify-start " block>
							<v-avatar :image="item.guestAvatar" size="small" class="my-1 mr-3"></v-avatar>
							{{ item.guestUsername }}
						</v-btn></td>
					<td class="text-start">
						<v-btn
								icon="mdi-play"
								size="x-small"
								color="primary"
								class="ma-0 pa-0 justify-center align-center"
								@click="streamUser(item.hostID)"
						></v-btn>
					</td>
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


