<!-- CHAT -->
<script setup lang="ts">
import NavSideBar from '../components/NavSideBar.vue'
import Chat from '@/components/Chat/Chat.vue'
import DialogWaiting from '@/components/Game/DialogWaiting.vue';
import DialogInvite from '@/components/Game/DialogInvite.vue';
import Notifications from '@/components/Notifications.vue';
import { usePlayerStore} from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

const playerStore = usePlayerStore()
const { user } = storeToRefs(playerStore)

// make user available to Chat.vue and reactivity
const userChat = user.value;



</script>

<template>
    <div class="chat">
        <div v-if="!userChat.locked">
        <NavSideBar/>
        <Notifications></Notifications>
        <DialogWaiting></DialogWaiting>
        <DialogInvite></DialogInvite>
        <Chat/>
        </div>
        <div v-else>
			WARNING : You can view one page at a time. Please close the other tabs. and reload this page. Page is locked: {{ user.locked }}
		</div>
    </div>
</template>

<style scoped>
.chat {
	background-color: white;
    width: 100%;
    height: 100%;
}
</style>