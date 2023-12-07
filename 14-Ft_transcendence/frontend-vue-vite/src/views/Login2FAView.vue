<script lang="ts">
import Dialog2FA from '../components/Profile/Dialog2FA.vue'

export default {
	components : {
		Dialog2FA,
	},
	data() {
		return {
		}
	},
}
</script>

<template>
	<v-card
		class="backgroundLogin login "
		variant="tonal"
	>
		<v-btn
			prepend-icon="mdi-shield-lock"
		>
			Two-factor authentication
			<Dialog2FA mode="login"></Dialog2FA>
		</v-btn>
	</v-card>
</template>


<style scoped>

.login {
	background-color: aqua;
	height: 100%;
	width: 100%;
	display: flex;
	justify-content: center;
	justify-items: center;
	align-content: center;
	align-items: center;

}

.backgroundLogin {
    position: absolute;
    top: 0;
    left: 0;
    transform: scale(1.1);
    background: url(../../cats_ai.webp) no-repeat center center;
    background-size: cover;
}
</style>