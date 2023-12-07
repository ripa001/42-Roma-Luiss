<script lang="ts">
import { defineComponent } from 'vue'
import axios from 'axios'

import { usePlayerStore } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

const playerStore = usePlayerStore()
const { user } = storeToRefs(playerStore)
const debug = false

export default defineComponent({
	components: {
	},
	data() {
		return {
			dialogBox: ! playerStore.isProfileCompleted(),
			// USERNAME
			username: '',
			isValidUsername : false,
			loadingUsername: false,
			successUsername: false,
			successMessageUsername: '',
			errorUsername: false,
			errorMessageUsername: '',
			usernameRules: [
				(value: string) => (value && value.length <= 15) || 'Name must be less than 15 characters',
				(value: string) => (value && value.length >= 5) || 'Name must be at least 5 characters',
				(value: string) => !/\s/.test(value) || 'Name must not contain whitespace',
				(value: string) => /^[a-zA-Z0-9]+$/.test(value) || 'Name must only contain letters and numbers',
			],
			// AVATAR
			file: [] as File[],
			fileToUpload: {} as File,
			avatarPreview: '',
			loadingAvatar: false,
			successAvatar: false,
			successMessageAvatar: '',
			errorAvatar: false,
			errorMessageAvatar: '',
			AvatarRules: [
				(value : File[]) => {
					return !value || !value.length || value[0].size < 2000000 || 'Avatar size should be less than 2 MB!'
				},
			],
		}
	},
	created() {
		axios.defaults.headers.common['Authorization'] = 'Bearer' + ' ' + localStorage.getItem('ft_transcendence_token');
		axios.defaults.baseURL = 'http://' + location.hostname + ':' + import.meta.env.VITE_BACKEND_PORT;
	},
	methods: {
		async setProfileasComplete() {
			try {
				await playerStore.setProfileAsComplete();
				this.dialogBox = false;
			}
			catch(err) {
				console.error(`could not send profile confirmation because of: ${err}`)
			}
		},
		async validate () {
			await this.$refs.form.validate()
			this.isValidUsername = this.$refs.form.isValid
		},
		reset () {
			this.$refs.form.reset()
		},
		displaySuccessAvatar(message: string) {
			this.successAvatar = true
			this.successMessageAvatar = message
		},
		displayErrorAvatar(message: string) {
			this.errorAvatar = true
			this.errorMessageAvatar = message
		},
		displaySuccessUsername(message: string) {
			this.successUsername = true
			this.successMessageUsername = message
		},
		displayErrorUsername(message: string) {
			this.errorUsername = true
			this.errorMessageUsername = message
		},
		async sendUsername(){
			if (debug) console.log('| DialogEdit | methods | sendUsername()')
			this.loadingUsername = true
			if (debug) console.log(`username : ${this.username}`)
			axios
				.patch(`players/me`, 
					{
						username: this.username
					}
				)
				.then(async () => {
					playerStore.updateUsername()
					this.displaySuccessUsername("Successfully uploaded a new username !")
					this.loadingUsername = false
				})
				.catch((error : any) => {
					// Handle errors
					if (error.response) {
						// The request was made and the server responded with a status code
						// that falls out of the range of 2xx
						console.log('Logging response error:', error.response.data);
						this.displayErrorUsername(
							`${error.response.data.message} (status code ${error.response.data.statusCode})`
							)
					} else if (error.request) {
						// The request was made but no response was received
						console.log('Logging request error:', error.request);
						this.displayErrorUsername('Error: No response from server.')
					} else {
						// Something happened in setting up the request that triggered an Error
						console.log('Logging general error:', error.message);
						this.displayErrorUsername('Error: Bad request.')
					}
				})
				.finally(() => (this.loadingUsername = false))
		},
		sendAvatar(){
			if (debug) console.log('| DialogEdit | methods | sendAvatar()')
			this.loadingAvatar = true

			let formData = new FormData();
			formData.append("avatar", this.fileToUpload);

			axios
				.put(`players/me/avatar`, formData, {
						headers: {
							"Content-Type": "multipart/form-data"
						},
					}
				)
				.then(() => {
					playerStore.updateAvatar()
					this.displaySuccessAvatar("Successfully uploaded a new avatar picture !")
				})
				.catch((error) => {
					this.displayErrorAvatar('Error: Server internal error.')
					console.error(error)
				})
				.finally(() => (this.loadingAvatar = false))
		},
		onFileInput(event : any) {
			if (this.errorAvatar == true)
				this.errorAvatar = false
			if (true == (!event.target.files || !event.target.files.length || event.target.files[0].size >= 2000000))
				this.errorAvatar = true
			else {
				this.fileToUpload = event.target.files[0]
				const data = URL.createObjectURL(event.target.files[0])
				this.avatarPreview = data
				event.target.value
			}
		},
		onFileRemove() {    	   
			this.avatarPreview = ''
			this.errorAvatar = false
		}
	},
	watch: {
		successUsername(isActive : boolean) {
			if (isActive == true) {
				this.errorUsername = false
			}
		},
		successAvatar(isActive : boolean) {
			if (isActive == true) {
				this.errorAvatar = false
				this.errorMessageAvatar = ''
			} else {
				this.successMessageAvatar = ''
			}
		},
		errorAvatar(isActive : boolean) {
			if (isActive == true) {
				this.successAvatar = false
				this.successMessageAvatar = ''
			} else {
				this.errorMessageAvatar = ''
			}
		},
		// reset variables when dialog is opened
		dialogBox(isActive: boolean) {
			if (isActive == true) {
				this.username = ''
				this.isValidUsername = false
				this.successUsername = false
				this.successMessageUsername = ''
				this.errorUsername = false
				this.errorMessageUsername = ''
				this.loadingUsername = false

				this.successAvatar = false
				this.successMessageAvatar = ''
				this.errorAvatar = false
				this.errorMessageAvatar = ''
				this.loadingAvatar = false
				this.avatarPreview = ''
			} 
		}
	},
	mounted() {}
})
</script>

<template>
	<v-dialog v-model="dialogBox" activator="parent">
		<v-card rounded class="dialog bg-white ma-auto pa-4 w-75">
			<v-card-title class="text-button">Edit profile information</v-card-title>
			<v-card-item >
				<h3 class="text-overline">Username</h3>
				<h4 class="font-weight-light">Change your username</h4>
				<v-form
					ref="form"
				>
					<v-text-field
						v-model="username"
						:loading="loadingUsername"
						:counter="15"
						:rules="usernameRules"
						clearable
						@click:clear="reset()"
						@update:model-value="validate()"
						:messages="successMessageUsername"

						label="Username"
						placeholder="Choose username"
						density="compact" 
						color="primary"
						prepend-icon="mdi-account-edit"
						clear-icon="mdi-close-circle-outline"
						variant="outlined"
						class="my-2"
					></v-text-field>
					<v-btn v-show="isValidUsername" text="Upload" @click="sendUsername" size="small" border color="primary" variant="elevated"></v-btn>
				</v-form>
				<v-alert v-model="errorUsername" color="error" density="compact" class="my-3">{{ errorMessageUsername }}</v-alert>
				<!-- <v-alert v-model="successUsername" color="success" density="compact" class="my-3">{{ successMessageUsername }}</v-alert> -->
			</v-card-item>

			
				<v-card-item>
				<h3 class="text-overline">Avatar</h3>
				<h4 class="font-weight-light">Choose an image for your new avatar. Maximum size 2M.</h4>
				<v-file-input
					:model-value="file"
					:loading="loadingAvatar"
					:error="errorAvatar"
					:error-messages="errorMessageAvatar"
					accept="image/*"
					:rules="AvatarRules"
					:messages="successMessageAvatar"
					@click:clear="onFileRemove()"
					@change="onFileInput($event)"
					
					label="Choose avatar"
					density="compact"
					chips
					show-size
					color="primary"
					prepend-icon="mdi-image-edit"
					clear-icon="mdi-close-circle-outline"
					variant="outlined" 
					class="my-2"
				>
				</v-file-input>
			</v-card-item>

			<v-expand-transition>
				<v-card-item v-show="avatarPreview" >
					<div class="align-center justify-center pa-0 ma-0 d-flex flex-column ">
						<h4 class="font-weight-light mb-4">Preview</h4>
						<v-avatar
							:image="avatarPreview"
							size="200"
							variant="elevated"
						>
						</v-avatar>
					</div>
					<v-card-text class="px-0 font-weight-light ">Click on 'upload' to confirm the change</v-card-text>
					<v-btn text="Upload" @click="sendAvatar" size="small" border color="primary" variant="elevated"></v-btn>
					<v-alert v-model="errorAvatar" color="error" density="compact" class="my-3">{{ errorMessageAvatar }}</v-alert>
					<!-- <v-alert v-model="successAvatar" color="success" density="compact" class="my-3">{{ successMessageAvatar }}</v-alert> -->
				</v-card-item>
			</v-expand-transition>

			<v-card-item class="text-end">
				<v-btn text="Close" size="large" @click="setProfileasComplete" border class="me-4" color="primary" variant="tonal"></v-btn>
			</v-card-item>
		</v-card>
	</v-dialog>
</template>

<style scoped>

</style>