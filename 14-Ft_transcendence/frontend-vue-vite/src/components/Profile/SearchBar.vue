<script lang="ts">
import { usePlayerStore, type Player } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'
import CatSnackBar from '@/components/Utils/CatSnackBar.vue'

const playerStore = usePlayerStore()
const { user } = storeToRefs(playerStore)

const debug = false

export default {
	components: {
		CatSnackBar
},
	data() {
		return {
			loading : false,
			snackbar : false,
			snackbarText : '',
		}
	},
	computed: {
		publicUsers() : Player[] {
			return playerStore.publicUsers;
		}
	},
	methods: {
		async addAsFriend(id : number, username : string){
			if (debug) console.log(`addAsFriend: userProfile.id = ${id}, typeof is: ${typeof id}`)
			playerStore.sendFriendshipRequest(Number(id));
			this.snackbar = true,
			this.snackbarText = 'Request sent to ' + username;
		},
		customFilter (itemTitle : string, queryText : string, item : any) {
			// if (debug) console.log('| SearchBar | methods | customFilter() '  + itemTitle)
			const textOne = item.raw.username.toLowerCase()
			const textTwo = item.raw.firstName.toLowerCase()
			const textThree = item.raw.lastName.toLowerCase()
			const searchText = queryText.toLowerCase()

			return (
				textOne.indexOf(searchText) > -1 ||
				textTwo.indexOf(searchText) > -1 ||
				textThree.indexOf(searchText) > -1
			)
		},
	},
	watch : {
		snackbar(newValue : boolean){
			if (newValue == false)
				this.snackbarText = ''
		}
	},
	beforeCreate() {
	if (debug) console.log('| SearchBar | beforeCreate()' )
	},
	created() {
		if (debug) console.log('| SearchBar | created(' + (user.value.id) + ')')
	},
	beforeMount() {
		if (debug) console.log('| SearchBar | beforeMount(' + (user.value.id) + ')')
	},
	mounted() {
		if (debug) console.log('| SearchBar | mounted(' + (user.value.id) + ')')
	},
	beforeUpdate() {
		if (debug) console.log('| SearchBar | beforeUpdate(' + (user.value.id) + ')')
	},
	updated() {
		if (debug) console.log('| SearchBar | updated(' + (user.value.id) + ')')
	},
	beforeUnmount() {
		if (debug) console.log('| SearchBar | beforeUnmount(' + (user.value.id) + ')')
	},
	unmounted() {
		if (debug) console.log('| SearchBar | unmounted(' + (user.value.id) + ')')
	},
}
</script>

<template>
	<v-card
		class="SearchBar d-flex justify-center flex-wrap "
		variant="flat"
		:loading="loading"
	>
		<v-responsive
		max-width="550"
		min-width="fit-content"
		>
			<CatSnackBar
				@closeSnackbar="snackbar = false"
				:snackbarText="snackbarText"
				:snackbarParent="snackbar"
			></CatSnackBar>

			<v-autocomplete
				:items="publicUsers"
				auto-select-first
				item-props
				menu-icon=""
				item-title="username"
				item-value="username"
				:custom-filter="customFilter"

				prepend-inner-icon="mdi-magnify"
				label="Search a Player"
				color="primary"
				clearable
				clear-icon="mdi-close-circle"
				no-data-text="No existing user"

				class="flex-full-width pa-1 ma-1"
				density="compact"
				rounded
				variant="outlined"
				bg-color="white"
			>

				<template v-slot:item="{ props, item }">
					<v-list-item class="ma-0 pa-1">
						<div
							style="
								display:inline-flex;
								justify-content: space-between;
								width: 100%;
								"
						>
							<v-list-item 
								style="flex-grow: 2;"
								v-bind="props"
								:to="{ name: 'profile', params: { id: item?.raw?.id } }"
								:title="item?.raw?.username"
								:subtitle="item?.raw?.firstName + ' ' +  item?.raw?.lastName"
								:prepend-avatar="item?.raw?.avatar"
								rounded="xl"
								append-icon="mdi-account-eye"
							>
								<template v-slot:prepend>
									<v-avatar size="small"> </v-avatar>
								</template>
								<template v-slot:append>
									<v-icon color="primary" class="ma-0 pa-0"> </v-icon>
								</template>
						</v-list-item>
							<v-list-item>
								<v-btn
									@click="addAsFriend(item?.raw?.id, item?.raw?.username)"
									icon="mdi-account-plus"
									color="primary"
									variant="tonal"
									size="small"
									ripple
								>
								</v-btn>								
							</v-list-item>

						</div>
					</v-list-item>
				</template>

			</v-autocomplete>
		</v-responsive>
	</v-card>
</template>

<style scoped>
.SearchBar {
	background-color: transparent;
}


</style>
