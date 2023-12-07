<script lang="ts">
import { usePlayerStore, type Player, PlayerStatus } from '@/stores/PlayerStore'
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
			user : user,
			friends : friends,
        }
    },
	computed: {
		visibility() : 'Loading' | 'MyProfile' | 'FriendProfile' | 'PublicProfile' | 'BlockedProfile'  {
			if (this.userProfile != undefined)
				return playerStore.visibility(this.userProfile?.id);
			return 'Loading'
		},
		status() : string {
			if (this.userProfile != undefined){
				if (this.visibility === 'MyProfile')
					return this.user.status
				if (this.visibility === 'FriendProfile'){
					for (const friend of this.friends) {
						if (friend.id === this.userProfile?.id)
							return friend.status;
					}				
				}				
			}
			return ''
		},
		badgeColor() : string {
			if (this.status == PlayerStatus.playing)
				return 'blue'
			else if (this.status == PlayerStatus.online)
				return 'green'
			else
				return 'grey'
		},
	},
	watch : {
		userProfile(newValue : Player) {
			if (debug) console.log('| Avatar | watch | userProfile : new value : ' + newValue.username)
		},
		visibility(newValue : 'MyProfile' | 'FriendProfile' | 'PublicProfile' | 'BlockedProfile') {
			if (debug) console.log('| Avatar | watch | visibility : new value : ' + newValue)
		},
		status(newValue : string) {
			if (debug) console.log('| Avatar | watch | status : new value : ' + newValue)
		},
		badgeColor(newValue : string) {
			if (debug) console.log('| Avatar | watch | badgeColor : new value : ' + newValue)
		},
	},
}
</script>

<template>
		<v-card
			v-if="userProfile != undefined"
			class="itemAvatar" density="comfortable" variant="flat"
		>

			<v-badge
				v-if="visibility === 'MyProfile' || visibility === 'FriendProfile'"
				bordered inline
				:color="badgeColor" 
				:content="status">
				<v-avatar size="130" rounded="1">
					<v-img cover :src="userProfile?.avatar"></v-img>
				</v-avatar>
			</v-badge>

			<v-avatar
				v-if="visibility === 'PublicProfile' || visibility === 'BlockedProfile'"
				size="130" rounded="1">
				<v-img cover :src="userProfile?.avatar"></v-img>
			</v-avatar>

			<div class="backgroundItem ma-3">
				<v-card-item
					:title="userProfile?.username"
					:subtitle="userProfile?.firstName + ' ' + userProfile?.lastName"
				></v-card-item>
			</div>
		</v-card>

</template>

<style>
.itemAvatar {
	display: flex;
	flex-direction: column;
	margin: 1%;
	padding: 1%;
	/* background-color: aquamarine; */
	background-color: transparent;
}

.backgroundItem {
	background-color: rgba(255, 255, 255, 0.497);
	color: black;
	border-radius: 30px; /*Increase or decrease the value for controlling the roundness*/
	width: fit-content;
}

.itemAvatar .v-badge__badge {
	color: antiquewhite !important;
}
</style>