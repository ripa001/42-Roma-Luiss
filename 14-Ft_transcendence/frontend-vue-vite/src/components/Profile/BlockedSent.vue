<script lang="ts">
import { usePlayerStore, type Player } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

const playerStore = usePlayerStore()
const { blockedUsers, pendingUsers } = storeToRefs(playerStore)

const debug = false

export default {
	components:	{
},
	data: () => ({
		showBlackList: false,
		showSentRequestList: false,
	}),
	computed : {
		blockedUsers() : Player[] {
			return blockedUsers.value
		},
		pendingUsers() : Player[] {
			return pendingUsers.value
		}
	},
	watch : {
		showBlackList(newValue : Boolean){
			if (newValue == true)
				this.showSentRequestList = false
		},
		showSentRequestList(newValue : Boolean){
			if (newValue == true)
				this.showBlackList = false
		}
	},
	beforeCreate() {
	if (debug) console.log('| BlockedSent | beforeCreate()')
	},
	created() {
		if (debug) console.log('| BlockedSent | created()')
	},
	beforeMount() {
		if (debug) console.log('| BlockedSent | beforeMount()')
	},
	mounted() {
		if (debug) console.log('| BlockedSent | mounted()')
	},
	beforeUpdate() {
		if (debug) console.log('| BlockedSent | beforeUpdate()')
	},
	updated() {
		if (debug) console.log('| BlockedSent | updated()')
	},
	beforeUnmount() {
		if (debug) console.log('| BlockedSent | beforeUnmount()')
	},
	unmounted() {
		if (debug) console.log('| BlockedSent | unmounted()')
	},
	}
</script>
  


<template>
	<v-card
		class="component justify-center align-center"	
		min-width="300"
	>
		<v-card-item
			density="compact"
		>
			<v-card-subtitle
				class="text-overline"
				style="font-style: italic;"
			>
			{{ showBlackList ? 'Blacklisted' :  showSentRequestList ? 'Sent requests' : ''}}
			</v-card-subtitle>

			<template v-slot:prepend>
				<v-btn
					:icon="showBlackList ? 'mdi-skull-outline' : 'mdi-skull'"
					size="small"
					variant="tonal"
					class="mr-1"
					:color="showBlackList ? 'primary' : 'grey'"
					@click="showBlackList = !showBlackList"
				>
				</v-btn>
				<v-btn
					:icon="showSentRequestList ? 'mdi-send-outline' : 'mdi-send'"
					size="small"
					variant="tonal"
					class="ml-1"
					:color="showSentRequestList ? 'primary' : 'grey'"
					@click="showSentRequestList = !showSentRequestList"
				>
				</v-btn>
			</template>
		</v-card-item>

		<v-card-item
			class="px-2 py-0 ma-0"
			v-if="showBlackList == true"
		>
			<v-divider></v-divider>

			<v-card-item
				class="ma-0 pa-0"
			>
				<v-virtual-scroll
					:items="blockedUsers"
					height="95%"
				>
					<template v-slot:default="{ item }">
						<v-list-item
							:to="{ name: 'profile', params: { id: item.id } }"
							:title="item.username" 
							:prepend-avatar="item.avatar"
							class=" ma-1 pa-2 rounded-pill"
							variant="text"
						>
						</v-list-item>
					</template>
				</v-virtual-scroll>			
			</v-card-item>
		</v-card-item>

		<v-card-item
			class="px-2 py-0 ma-0"
			v-if="showSentRequestList == true"
		>
			<v-divider></v-divider>

			<v-card-item
				class="ma-0 pa-0"
			>
				<v-virtual-scroll
					:items="pendingUsers"
					height="95%"
				>
					<template v-slot:default="{ item }">
						<v-list-item
							:to="{ name: 'profile', params: { id: item.id } }"
							:title="item.username" 
							:prepend-avatar="item.avatar"
							class=" ma-1 pa-2 rounded-pill"
							variant="text"
						>
						</v-list-item>
					</template>
				</v-virtual-scroll>			
			</v-card-item>
		</v-card-item>
	</v-card>
</template>

<style scoped>
.component {
	max-width:  100%;
	max-height:  100%;
	width: fit-content;
}

</style>