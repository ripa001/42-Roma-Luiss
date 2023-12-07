<script lang="ts">
const debug = false

export default {
	props: {
		snackbarParent : {
			type: Boolean,
			required: true
		},
		snackbarText: {
			type: String,
			required: true
		},
		color : {
			type: String,
			required: false
		},
	},
	emits : [
		'closeSnackbar'
	],
	data() {
		return {
			snackbar : false
		}
	},
	watch : {
		snackbarParent(newValue : boolean){
			this.snackbar = newValue
		}
	},
	methods: {
	}
}
</script>

<template>
	<v-snackbar
		v-model="snackbar"
		timeout=5000
		location="top"
		:color="color ? color : 'primary'"
		rounded="xl"
	>
		<v-icon icon="mdi-cat" class="mr-2"></v-icon>
		{{ snackbarText }}
		<template v-slot:actions>
			<v-btn
				color="white"
				variant="tonal"
				@click="$emit('closeSnackbar')"
				rounded="xl"
			>
				Close
			</v-btn>
		</template>
	</v-snackbar>
</template>

<style scoped>

</style>