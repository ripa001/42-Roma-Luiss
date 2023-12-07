<script lang="ts">

import NavSideBar from '../components/NavSideBar.vue'
import Notifications from '@/components/Notifications.vue'
import UserCard from '../components/Profile/UserCard.vue'
import MatchHistoryTable from '../components/Profile/MatchHistoryTable.vue'
import AddFriend from '@/components/Profile/AddFriend.vue'
import Friends from '../components/Profile/Friends.vue'
import Achievements from '../components/Profile/Achievements.vue'
import BlockedSent from '@/components/Profile/BlockedSent.vue'
import DialogWaiting from '@/components/Game/DialogWaiting.vue'
import DialogInvite from '@/components/Game/DialogInvite.vue'
import Debug from '@/components/Debug.vue'
import { storeToRefs } from 'pinia'

import { usePlayerStore, type Player } from '@/stores/PlayerStore'

const playerStore = usePlayerStore()
const { user, friends, blockedUsers, fetchPlayer } = storeToRefs(playerStore)
const debug = false

export default {
	components: {
		NavSideBar, UserCard, MatchHistoryTable, AddFriend, Friends, Achievements,
		Notifications,
		BlockedSent,
		DialogWaiting,
		DialogInvite,
		Debug
	},
	data() {
		return {
			userVisitor: user,
			userVisitorFriends: friends,
			userProfile: undefined as Player | undefined,
		}
	},
	computed: {
		visibility(): 'Loading' | 'MyProfile' | 'FriendProfile' | 'PublicProfile' | 'BlockedProfile' {
			if (debug) console.log('| ProfileView | computed | visibility')
			if (this.userProfile != undefined) {
				if (user.value.id == this.userProfile.id)
					return 'MyProfile'
				for (const friend of friends.value) {
					if (friend.id == this.userProfile.id) {
						return 'FriendProfile'
					}
				}
				for (const blocked of blockedUsers.value) {
					if (blocked.id == this.userProfile.id) {
						return 'BlockedProfile';
					}
				}
				return "PublicProfile";
			}
			else
				return 'Loading'
		},
	},
	methods: {
		async fetchUserProfile() {
			let profileID: number = Number(this.$route.params.id)
			if (debug) console.log(`| ProfileView | methods | fetchUserProfile() | ${profileID}`)

			if (!profileID || profileID == this.userVisitor.id) {
				if (debug) console.log(`Visitor and userProfile are the same`)
				this.userProfile = this.userVisitor;
			}
			else {
				try {
					this.userProfile = await fetchPlayer.value(profileID);
					if (debug) console.log(`{\
						userprofileID: ${this.userProfile?.id},\
						userprofileUsername: ${this.userProfile?.username},\
						userprofileAvatar: ${this.userProfile?.avatar},\
					}`)
				}
				catch (err) {
					console.error(`Cannot view selected user profile`);
					this.$router.push({ name: 'profile' });
				}
			}
			if (debug) console.log(`| ProfileView | methods | fetchUserProfile() | END`)
		},
	},
	watch: {
		userVisitor(newValue: Player) {
			if (debug) console.log('| ProfileView | watch | userVisitor : new value : ' + newValue.username)
		},
		userVisitorFriends(newValue: Player[]) {
			if (debug) console.log('| ProfileView | watch | userVisitorFriends : new length : ' + newValue.length)
		},
		userProfile(newValue: Player) {
			if (debug) console.log('| ProfileView | watch | userProfile : new value : ' + newValue.username)
		},
	},
	async created() {
		if (debug) console.log('| ProfileView | created(' + (this.userProfile?.id) + ')')
		await this.fetchUserProfile()

	},
	async beforeUpdate() {
		if (debug) console.log('| ProfileView | beforeUpdate(' + (this.userProfile?.id) + ')')
		try {
			await this.fetchUserProfile()
		}
		catch (_) {
			this.$router.push({ name: 'profile' });
		}
	},
}
</script>

<template>
	<div class="profile">
		<div v-if="!userVisitor.locked">
			<NavSideBar />
			<Notifications />
			<DialogWaiting></DialogWaiting>
			<DialogInvite></DialogInvite>
			<v-card class="parent">
				<v-card class="child1">
					<v-card class="child2">
						page is lock: {{ userVisitor.locked}}
						<UserCard v-if="userProfile != undefined" :userProfile="(userProfile as Player)"></UserCard>
					</v-card>
				</v-card>
				<v-card class="child1">
					<v-card class="child2"
						v-if="(userProfile != undefined) && (visibility === 'MyProfile' || visibility === 'FriendProfile' || visibility === 'PublicProfile')">
						<Achievements :userProfile="(userProfile as Player) || undefined"
							v-if="(userProfile != undefined) && (visibility === 'MyProfile' || visibility === 'FriendProfile')">
						</Achievements>
						<MatchHistoryTable :userProfile="(userProfile as Player) || undefined"
							v-if="(userProfile != undefined) && (visibility === 'MyProfile' || visibility === 'FriendProfile' || visibility === 'PublicProfile')">
						</MatchHistoryTable>
					</v-card>
					<v-card class="child2" v-if="visibility === 'MyProfile'">
						<AddFriend />
						<Friends />
						<BlockedSent />
					</v-card>
				</v-card>
			</v-card>
		</div>
		<div v-else>
			WARNING : You can view one page at a time. Please close the other tabs. and reload this page. Page is locked: {{
				userVisitor.locked }}
		</div>
	</div>
</template>

<style scoped>
.parent {
	display: flex;
	flex-direction: column;
	/* x and y axis inverted */
	align-items: center;
	/* y axis */
	justify-content: start;
	/* x axis */
	justify-items: start;
	/* x axis */
	width: 100%;
	height: 100%;
}

.child1 {
	display: flex;
	flex-direction: row;
	align-items: start;
	/* y axis */
	align-content: start;
	/* y axis */
	justify-content: start;
	/* x axis */
	justify-items: start;
	/* x axis */
	width: 100%;
	height: 100%;
}

.child2 {
	display: flex;
	flex-direction: column;
	/* x and y axis inverted */
	align-items: stretch;
	/* y axis */
	align-content: center;
	/* y axis */
	justify-content: start;
	/* x axis */
	justify-items: center;
	/* x axis */
	width: 100%;
	height: 100%;
}</style>
