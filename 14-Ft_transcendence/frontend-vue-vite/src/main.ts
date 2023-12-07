import './assets/main.css'
// import Vue from 'vue'
import axios from 'axios'
import VueAxios from 'vue-axios'

import { createApp } from 'vue'
import { createPinia } from 'pinia'

import VuetifyInstance from './plugins/vuetify'

import App from './App.vue'
import router from './router'

const app = createApp(App)

app.use(createPinia())
app.use(router)
app.use(VuetifyInstance)
app.use(VueAxios, axios)

app.config.globalProperties.$http = axios

app.mount('#app')
