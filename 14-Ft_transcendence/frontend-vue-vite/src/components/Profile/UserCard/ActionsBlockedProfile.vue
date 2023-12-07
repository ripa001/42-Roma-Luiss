<script lang="ts">
import { usePlayerStore, PlayerStatus, type Player } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

const playerStore = usePlayerStore()
const { user, friends } = storeToRefs(playerStore)
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
			loading: false,
			state: 'default'
        }
    },
    methods: {
		unblockUser() {
			if (this.userProfile != undefined)
				playerStore.toggleBlockUser(this.userProfile?.id, false)
		}
	},
    mounted (){
    },
}
</script>

<template>
	<v-card
		v-if="userProfile != undefined"
		class="itemActions itemActionsPublicProfile"
		density="compact"
		variant="flat"
	>
		<v-btn 
			value="unblock"
			@click="unblockUser"
			:text="'Unblock ' + `${userProfile?.username}`"
			prepend-icon="mdi-account-plus"
			:color="state == 'pending'? 'purple-lighten-4' : 'white'"
			block
		>
		</v-btn>
	</v-card>
</template>

<style>
.itemActions {
	display: flex;
	flex-direction: column;
	margin: 1%;
	padding: 1%;
	/* background-color: rgb(13, 114, 78); */
	background-color: transparent;
}

.backgroundItem {
	background-color: rgba(255, 255, 255, 0.497);
	color: black;
	border-radius: 30px; /*Increase or decrease the value for controlling the roundness*/
	width: fit-content;
}

</style>