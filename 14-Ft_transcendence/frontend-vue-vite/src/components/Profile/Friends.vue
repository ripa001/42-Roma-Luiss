<script lang="ts">
import { usePlayerStore, PlayerStatus, type Player } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

const playerStore = usePlayerStore()
const { friends } = storeToRefs(playerStore)
const debug = false

export default {
	components:	{
	},
	data: () => ({
		badgeColor: 'grey',
	}),
	computed : {
		items() : Player[] {
			return friends.value
		}
	},
	methods : {
		getBadgeColor(status : PlayerStatus) : string {
			if (debug) console.log('| Friends | methods | getBadgeColor()')
			if (status == PlayerStatus.online) return 'green'
			else if (status == PlayerStatus.playing) return 'blue'
			else return 'grey'			
		}
	},
	beforeCreate() {
		if (debug) console.log('| Friends | beforeCreate()')
	},
	created() {
		if (debug) console.log('| Friends | created(' + (this.items.length) + ')')
	},
	beforeMount() {
		if (debug) console.log('| Friends | beforeMount(' + (this.items.length) + ')')
	},
	mounted() {
		if (debug) console.log('| Friends | mounted(' + (this.items.length) + ')')
	},
	beforeUpdate() {
		if (debug) console.log('| Friends | beforeUpdate(' + (this.items.length) + ')')
	},
	updated() {
		if (debug) console.log('| Friends | updated(' + (this.items.length) + ')')
	},
	beforeUnmount() {
		if (debug) console.log('| Friends | beforeUnmount(' + (this.items.length) + ')')
	},
	unmounted() {
		if (debug) console.log('| Friends | unmounted(' + (this.items.length) + ')')
	},
}
</script>

<template>
	<v-card
		class="component"
		min-width="300"
	>
		<v-card-item>
			<v-card-title class="text-overline">My friends</v-card-title>
		</v-card-item>
		<v-divider></v-divider>
		<v-card-text v-if="items.length === 0">You have no friends for now!</v-card-text>
		<v-virtual-scroll
			:items="items"
			height="95%"
		>
			<template v-slot:default="{ item }">
				<v-list-item
					:title="item.username" 
					:subtitle="item.status"
					:to="{ name: 'profile', params: { id: item.id } }"
					class=" ma-1 pa-2 rounded-pill"
					variant="text"
				>
					<template v-slot:prepend>
						<v-badge dot :color="getBadgeColor(item.status)">
							<v-avatar
								:image="item.avatar" 
							>
							</v-avatar>
						</v-badge>
					</template>
				</v-list-item>
			</template>
		</v-virtual-scroll>
	</v-card>
</template>


<style scoped>
.component {
	max-width:  100%;
	max-height:  100%;
	width: fit-content;
}

</style>