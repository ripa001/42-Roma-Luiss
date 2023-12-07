<script lang="ts">

export default {
  setup() {
    const loginUrl = `http://${location.hostname}:${import.meta.env.VITE_BACKEND_PORT}/auth/42`

    return {
      loginUrl
    }
  },

  mounted() {}
}
</script>

<template>
	<v-card
		class="backgroundLogin login "
		variant="tonal"
	>
		<v-btn
			prepend-icon="mdi-login"
			:href="loginUrl"
			text="Login now !"
		>
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