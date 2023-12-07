<script lang="ts">
import { defineComponent } from 'vue'
import { usePlayerStore, type FriendRequest, type FriendRequestStatus } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

const playerStore = usePlayerStore()
const { notifications } = storeToRefs(playerStore)
const debug = false

export default defineComponent({
	components: {
	},
	data() {
		return {
			notificationList: notifications
		}
	},
	methods: {
		acceptFriend(request : (FriendRequest & FriendRequestStatus)){
			if (debug) console.log('| Notifications | methods | acceptFriend()' + request)
			request.status = 'loading'

			playerStore.sendFriendshipConsent(request.requestorID);
			//TODO add trigger to reload friends in Playerstore
		},
		rejectFriend(request : (FriendRequest & FriendRequestStatus)){
			if (debug) console.log('| Notifications | methods | rejectFriend()' + request)
			request.status = 'loading'

			playerStore.sendFriendshipRejection(request.requestorID);
		},
	},
	mounted() {
		if (debug) console.log('| Notifications | mounted')
		// this.notificationList = this.notificationList
		this.notificationList = notifications;
		// this.setNotificationsCount()
    },
})
</script>

<template>
	<v-app-bar
		floating
		location="top"
		class="mx-2 my-2"
		style="background-color: transparent;"
		flat
	>
		<template v-slot:append>
			<v-card	class="d-flex pa-3 justify-end align-start" color="transparent" flat>
				<v-menu max-height="150" :close-on-content-click=Boolean(false)>
					<template v-slot:activator="{ props }">
						<v-badge
							:content=notificationList.length
							color="error"
						>
							<v-btn
								v-bind="props"
								icon="mdi-bell"
								class="ma-0 pa-0 justify-center align-center NavSideBar"
								style="background-color: white;"
							>
							</v-btn>				
						</v-badge>
					</template>
					<v-list
					>
						<v-list-item-subtitle class="px-2 text-overline">Friend requests</v-list-item-subtitle>
						<v-list-item
							v-show="notificationList.length == 0"
						>No new friend request</v-list-item>
						<v-list-item
							v-for="(item, index) in notificationList"
							:key="index"
							:value="index"
							:title="item.requestorUsername"
							:prepend-avatar="item.requestorAvatar"
							density="compact"
							class="px-2"
						>
							<template v-slot:prepend>
								<v-avatar size="small"> </v-avatar>
							</template>			
							<template v-slot:append>
								<v-sheet class="pa-0 ml-2  ">
									<v-icon
										v-show="item.status == 'pending'"
										@click="acceptFriend(item)"
										icon="$success"
										color="success"
									>
									</v-icon>
									<v-icon
										v-show="item.status == 'pending'"
										@click="rejectFriend(item)"
										icon="$error"
										color="error"
										class="ml-1"
									> </v-icon>
									<v-progress-circular
										v-show="item.status == 'loading'"
										indeterminate
										rounded
										size="x-small"
										width="2"
										color="primary"
									>
									</v-progress-circular>
									<v-chip
										v-show="item.status == 'accepted'"
										size="x-small"
										color="success"
										text="accepted"
										variant="tonal"
									> </v-chip>
									<v-chip
										v-show="item.status == 'rejected'"
										size="x-small"
										color="info"
										text="rejected"
										variant="tonal"
									> </v-chip>
								</v-sheet>
							</template>
						</v-list-item>
					</v-list>
				</v-menu>
			</v-card>
		</template>
	</v-app-bar>
</template>

<style scoped>

</style>