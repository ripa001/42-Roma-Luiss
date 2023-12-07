<script lang="ts">
import { RouterView } from 'vue-router'
const debug = false

export default {
	components : {
	},
	data() {
		return {
		}
	},
	computed: {
	},
	methods: {
	},

	beforeCreate() {
		if (debug) console.log('| APP | beforeCreate()')
	},
	created() {
		if (debug) console.log('| APP | created()')
	},
	beforeMount() {
		if (debug) console.log('| APP | beforeMount()')
	},
	mounted() {
		if (debug) console.log('| APP | mounted()')
	},
	beforeUpdate() {
		if (debug) console.log('| APP | beforeUpdate()')
	},
	updated() {
		if (debug) console.log('| APP | updated()')
	},
	beforeUnmount() {
		if (debug) console.log('| APP | beforeUnmount()')
	},
	unmounted() {
		if (debug) console.log('| APP | unmounted()')
	},
}
</script>

<template>
	<v-app>
		<v-main>
			<RouterView></RouterView>
		</v-main>
	</v-app>
</template>


<style>
.v-app {
	height: 100dvh;
	width: 100dvw;
	align-content: center;
	justify-content: left;
}

.v-main {
	height: 100dvh;
	width: 100dvw;
	align-content: center;
	justify-content: left;
}

/* DEBUG STYLE */
.v-main {
	padding: 0.5%;
	margin: 0.5%;
}
.v-app {
	padding: 0.5%;
	margin: 0.5%;
}
.NavSideBar {
	background-color: rgba(255, 255, 255, 0.87);
}
.v-bottom-navigation {
	background-color: lemonchiffon;
}
.parent {
	background-color: rgb(209, 185, 239);
	padding: 0.5%;
	margin: 0.5%;
}
.child1 {
	padding: 0.5%;
	margin: 0.5%;
	background-color: lavender;
}
.child2 {
	padding: 0.5%;
	margin: 0.5%;
	background-color: lightgoldenrodyellow;
}

.component {
	padding: 1%;
	margin: 1%;
	background-color: white;
}

</style>

