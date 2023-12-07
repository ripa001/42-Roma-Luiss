<script lang="ts">
import { defineComponent } from 'vue'

export default defineComponent({
	components: {
	},
	data() {
		return {
			overlay : false,
			isGamePaused: false,
		}
	},
	watch : {
		overlay(newVal : Boolean){
			if (newVal == true)
				this.isGamePaused = true
			if (newVal == true)
			this.isGamePaused = false
		}
	}
})
</script>

<template>
	<v-app-bar
		floating
		location="bottom"
		class="mx-2 my-2"
		style="background-color: transparent;"
		flat
	>
		<template v-slot:append>
			<v-card	class="d-flex pa-3 justify-end align-start" color="transparent" flat>
					<!-- @click="overlay = true" -->
				<v-btn
					icon="mdi-help"
					class="ma-0 pa-0 justify-center align-center NavSideBar"
					style="background-color: white;"
				>

				</v-btn>				
				<v-overlay
					v-model="overlay"
					activator="parent"
					class="align-center justify-center"
				>
					<v-card
						class="pa-3 ma-3"
						>
						<v-card-title>How to play the game</v-card-title>
						<v-card-item>
							<v-card-text>
								<p>Move your paddle up and down to make the ball bounce and score in your opponent's territory !</p>
								<p>To win the game you need to score 10 points</p>
							</v-card-text>
							<v-card-text>Controls : use 'arrow up' and 'arrow down'</v-card-text>
							<v-card-text>you can exit the game at any time by clicking the exit button</v-card-text>
						</v-card-item>
					</v-card>
				</v-overlay>					
			</v-card>
		</template>
	</v-app-bar>
</template>

<style scoped>

</style>				