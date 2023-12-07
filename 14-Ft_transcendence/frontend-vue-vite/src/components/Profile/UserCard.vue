<script lang="ts">
import { usePlayerStore, PlayerStatus, type Player } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

import Notifications from '../Notifications.vue'
import Avatar from './UserCard/Avatar.vue'
import Stats from './UserCard/Stats.vue'
import ActionsPublicProfile from './UserCard/ActionsPublicProfile.vue'
import ActionsFriendProfile from './UserCard/ActionsFriendProfile.vue'
import ActionsMyProfile from './UserCard/ActionsMyProfile.vue'
import ActionsBlockedProfile from './UserCard/ActionsBlockedProfile.vue'

const playerStore = usePlayerStore()
const { user, friends } = storeToRefs(playerStore)
const debug = false

export default {
	components: {
    Notifications,
    Avatar,
    Stats,
    ActionsPublicProfile,
    ActionsFriendProfile,
    ActionsMyProfile,
    ActionsBlockedProfile
},
	props: {
		userProfile: {
			type: Object as () => Player || undefined,
			required: true
		},
	},
	data() {
		return {
			profileBackgroundUrl: `http://${location.hostname}:8080/cats.jpg`,
			userVisitor: user,
			userVisitorFriends: friends,
		}
	},
	computed: {
		visibility() : 'MyProfile' | 'FriendProfile' | 'PublicProfile' | 'BlockedProfile'  {
			if (debug) console.log('| UserCard | computed : visibility')
			let profileType = playerStore.visibility(this.userProfile.id);
			return profileType
		},
		debug() : boolean {
			return debug
		}
	},
	watch : {
		userVisitor(newValue : Player) {
			if (debug) console.log('| UserCard | watch | userVisitor : new value : ' + newValue.username)
		},
		userVisitorFriends(newValue : Player[]) {
			if (debug) console.log('| UserCard | watch | userVisitorFriends : new length : ' + newValue.length)
		},
		userProfile(newValue : Player) {
			if (debug) console.log('| UserCard | watch | userProfile : new value : ' + newValue.username)
		},
	},
	methods: {
	},
	beforeCreate() {
		if (debug) console.log('| UserCard | beforeCreate()')
	},
	created() {
		if (debug) console.log('| UserCard | created(' + (this.userProfile.id) + ')')
	},
	beforeMount() {
		if (debug) console.log('| UserCard | beforeMount(' + (this.userProfile.id) + ')')
	},
	mounted() {
		if (debug) console.log('| UserCard | mounted(' + (this.userProfile.id) + ')')
	},
	beforeUpdate() {
		if (debug) console.log('| UserCard | beforeUpdate(' + (this.userProfile.id) + ')')
	},
	updated() {
		if (debug) console.log('| UserCard | updated(' + (this.userProfile.id) + ')')
	},
	beforeUnmount() {
		if (debug) console.log('| UserCard | beforeUnmount(' + (this.userProfile.id) + ')')
	},
	unmounted() {
		if (debug) console.log('| UserCard | unmounted(' + (this.userProfile.id) + ')')
	},
}
</script>

<template>
	<p class="text-overline text-end mx-3 pa-0 " v-if="debug"> (debug) visibility : {{ visibility }}</p>

	<v-card
		class="containerContent component"
		:image="profileBackgroundUrl"
		rounded="1"
		variant="tonal"
	>

		<Avatar
			v-if="userProfile != undefined"
			:userProfile="userProfile"
		></Avatar>

		<Stats
			v-if="userProfile != undefined"
			:userProfile="userProfile"
		></Stats>

		<ActionsPublicProfile
			:userProfile="userProfile"
			v-if="(userProfile != undefined) && visibility == 'PublicProfile'"
		></ActionsPublicProfile>

		<ActionsFriendProfile
			:userProfile="userProfile"
			v-if="(userProfile != undefined) && visibility == 'FriendProfile'"
		></ActionsFriendProfile>

		<ActionsMyProfile
			v-if="(userProfile != undefined) && visibility == 'MyProfile'"
		></ActionsMyProfile>

		<ActionsBlockedProfile
			:userProfile="userProfile"
			v-if="(userProfile != undefined) && visibility == 'BlockedProfile'"
		></ActionsBlockedProfile>

		<!-- ADD BLOCKED PROFILE -->
	</v-card>
</template>

<style>
.containerContent {
	display: flex;
	flex-direction: row;
	align-content: start;
	/* align-items: stretch; */
	justify-content: space-between;
	/* justify-items: stretch; */
	/* height: 100%; */
	/* width: 100%; */
}

.containerContent .v-btn {
	margin: 5px;
	justify-content: start;
	min-height: fit-content;
	max-height: 20%;
	/* color: blue; */
	/* background-color: white; */
}

.containerContent .v-card__underlay {
	color: transparent;
}

.backgroundItem {
	background-color: rgba(255, 255, 255, 0.497);
	color: black;
	border-radius: 30px; /*Increase or decrease the value for controlling the roundness*/
	width: fit-content;
}
</style>
