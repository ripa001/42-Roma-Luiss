<script lang="ts">
import SearchBar from '@/components/Profile/SearchBar.vue'
const debug = false

export default {
	components:	{
    SearchBar,
},
	data: () => ({
		showBar: false,
	}),
	beforeCreate() {
	if (debug) console.log('| AddFriends | beforeCreate()')
	},
	created() {
		if (debug) console.log('| AddFriends | created()')
	},
	beforeMount() {
		if (debug) console.log('| AddFriends | beforeMount()')
	},
	mounted() {
		if (debug) console.log('| AddFriends | mounted()')
	},
	beforeUpdate() {
		if (debug) console.log('| AddFriends | beforeUpdate()')
	},
	updated() {
		if (debug) console.log('| AddFriends | updated()')
	},
	beforeUnmount() {
		if (debug) console.log('| AddFriends | beforeUnmount()')
	},
	unmounted() {
		if (debug) console.log('| AddFriends | unmounted()')
	},
	}
</script>
  


<template>
	<v-card
		class="component justify-center align-center"	
		min-width="300"
	>
		<v-card-item>
			<v-card-title class="text-overline">Add a new friend</v-card-title>
			<template v-slot:append>
				<v-btn
					:icon="showBar ? 'mdi-chevron-up' : 'mdi-plus'"
					size="small"
					variant="tonal"
					color="primary"
					@click="showBar = !showBar"
				>
				</v-btn>
			</template>
		</v-card-item>

		<v-card-item
			class="px-2 py-0 ma-0"
			v-if="showBar == true"
		>
			<SearchBar/>
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