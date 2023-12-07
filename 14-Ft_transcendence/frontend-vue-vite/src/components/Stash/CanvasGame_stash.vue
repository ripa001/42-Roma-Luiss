<script lang="ts">

/**
 * COSE DA FARE
 * 
 * 1. spostare lo stato del game nello store? : se lo faccio, probabilmente posso andare su un'altra pagina mentre sto giocando e mantenere la sessione di gioco
 * 		1.1 i web socket continueranno comunque ad aggiornare il gioco
 * 		1.2 i miei event listener su input utente saranno disabilitati
 * 		1.3 la mia paddle resterá ferma
 * 		1.4 se perdo mentre sono fuori, quando rientro vedo la schermata di fine gioco.
 * 
 * 2. fare una funzione che in base allo stato (gameConf), fa il clear del canvas e ridisegna il prossimo frame
 
 * 3. gestire gli event listener in questo file: forse é meglio mouse move, dove la coordinata del mouse mi dice se devo spostare il paddle sotto o sopra
 * 	3.1 magari solo quando sono nella mia metá campo
 *  3.2 magari guardando la coordinata y del mouse, se > di quella del paddle, il paddle va su, altrimenti giu
 *  3.3 idee migliori sono bene accette
 * 
 * 4. gestire le dimensioni : sia del canvas relativo alla intera window, sia degli oggetti (paddle, ball, etc.) relativamente al canvas
 * 		4.1 - il relativo  puó essere in % o in altre unitá di misura
 * 		4.2 soluzioni efficienti sono bene accette
 * 
 * 5. gestire il resize del canvas
 *	5.1 quando faccio il resize della finestra, il canvas cambia di dimensione e di conseguenza devono cambiare di dimensione
*	5.2 tutti quegli oggetti la cui dimensione dipende dal canvas

 * 6. gestire bene gli event listeners
 * 
 * 7. la parte di socket verrá dopo, adesso quello che é estremamente importante é avere una rappresentazione facilmente maneggiabile dello stato
 * 		7.1 fatta bene per future estensioni
 * 		7.2 fatta bene per poter integrare il canvas in piú parti della applicazione
 * 
 * 8. power-ups: different maps (per iniziare colori diversi), paddle height aumenta se fai punti, etc.
 */



 // TODO CHECK IF NEEDED
//  const requestAnimationFrame =
//   window.requestAnimationFrame ||
//   window.mozRequestAnimationFrame ||
//   window.webkitRequestAnimationFrame ||
//   window.msRequestAnimationFrame;

// const cancelAnimationFrame =
//   window.cancelAnimationFrame || window.mozCancelAnimationFrame;
// import { defineComponent } from 'vue'
import { usePlayerStore, type Player } from '@/stores/PlayerStore'
import { storeToRefs } from 'pinia'

const playerStore = usePlayerStore()
const { user, currentGame } = storeToRefs(playerStore)

const debug = false

export interface PlayerConf {
	id: number,
	paddleWidth: number,
	paddleHeight: number,
	paddlePos: {x: number, y: number}
}

export interface BallConf {
	start: {x: number, y: number},
	pos: {x: number, y: number},
	dir: {x: number, y: number},
	radius: number,
	color: string,
	speedFactor : number,
}

export interface GameConf {
	host: PlayerConf,
	guest: PlayerConf,
	ball : BallConf,
	pitchLineWidth: number,
	pitchCirclePos: {x: number, y: number},
	pitchCircleRadius: number,
}

const initialGameConf : GameConf = {
	host: {
		id: 0,
		paddleHeight: 0,
		paddlePos: {x: 0, y: 0},
		paddleWidth: 0,
	},
	guest: {
		id: 0,
		paddleHeight: 0,
		paddlePos: {x: 0, y: 0},
		paddleWidth: 0,
	},
	ball : {
		start: {x: 0, y: 0},
		pos: {x: 0, y: 0},
		dir: {x: 0, y: 0},
		radius: 0,
		color: 'purple',
		speedFactor: 500/1000, // px/sec (1000 milliseconds) pb when screen resize, different speed
	},
	pitchLineWidth: 0,
	pitchCirclePos: {x: 0, y: 0},
	pitchCircleRadius: 0,
}

export interface GameState {
	// host: PlayerConf,
	// guest: PlayerConf,
	// ball : BallConf,
	// pitchLineWidth: number,
	// pitchCirclePos: {x: number, y: number},
	// pitchCircleRadius: Number,
	// // paddleColor: string,
	// // pitchColor: string,
}

export interface TimeState {
	start: number;	// start of game abs nb performance.now(), gets fired with startGame()
	pause: number; // cumulates all off time incl pause, lag, wait
	clock: number; // cumulates actual running time of game
	lastTimeStamp: number; // last update
	deltaTime: number; // last time gap between screen updates
	getSeconds: (milliseconds: number) => number;   // function to calculate seconds from milliseconds
	getMinutes: (milliseconds: number) => number;   // function to calculate minutes from milliseconds
}

const initialTimeState : TimeState = {
	start: 0,
	pause: 0,
	clock: 0,
	deltaTime: 0,
	lastTimeStamp : 0,
	getSeconds(milliseconds) {
		return Math.floor((milliseconds / 1000) % 60)
	},
	getMinutes(milliseconds) {
		return Math.floor((milliseconds / 1000) / 60)
	},
}


export default {
	components:	{
	},
	data: () => ({
			// conf
			user : user.value,
			opponent : {} as Player,
			canvas_old_width: 0,
			canvas_old_height: 0,
			canvas : null as HTMLCanvasElement | null,
			ccontext: null as CanvasRenderingContext2D | null,

			gameConf: initialGameConf, // should be given by server ?
			// state
			start : false,
			paused: false,

			keyState: new Map<string, Boolean>([
				['ArrowUp', false], ['ArrowDown', false], [' ', false]
			]),



			// to put in a structure to pass to server
			gameTime : initialTimeState,
			score : {host : 0, guest : 0},

			hostPaddleDis: 0,
			guestPaddleDis: 0,

			ballDisY: 0,
			ballDisX: 0,

			ballDirX: 1,
			ballDirY: 1,
	}),
	watch : {
		gameStatus(newVal : 'undefined' | 'building' | 'playing' | 'end'){
			if (debug) console.log('| CanvasGame | watchers | Game status : ' + newVal)
			if (newVal == 'undefined')
				this.onLeaving()
			if (newVal == 'playing'){
				// this.canvasSetup();
				// this.countdown();
				// this.gameLoop();
			}
		},
		gameState(newVal: 'Start' | 'Play' | 'Pause' | 'End') {
			// if (debug) console.log("Game state : " + newVal)
		},
		// COLLISIONS
		ballDirX(newVal : number){
			if (newVal == 1){
				if (debug) console.log('Host lost a point')
				// send point request to server
				this.score.guest++				
			}

			if (newVal == -1){
				if (debug) console.log('Guest lost a point')
				// send point request to server
				this.score.host++				
			}
		},
		// use for bonus ? additional animation ?
		// ballDirY(newVal : number){
		// 	if (newVal == 1)
		// 		if (debug) console.log('Bouncing off ceiling')
		// 	if (newVal == -1)
		// 		if (debug) console.log('Bouncing off floor')
		// },
	},
	computed : {
		host() : Player {
			return currentGame.value.host
		},
		guest() : Player {
			return currentGame.value.guest
		},
		gameInfo() : {hostID: number, guestID: number, watcher: boolean} {
			return currentGame.value.gameInfo
		},
		gameStatus() : 'undefined' | 'building' | 'playing' | 'end' {
			return currentGame.value.status
		},
		endReason() : 'undefined' | 'hostWin' | 'guestWin' | 'userLeft' | 'aPlayerLeft' | 'opponentLeft' {
			return currentGame.value.endReason
		},
		streaming() : boolean {
			return (currentGame.value.status == 'playing' && currentGame.value.gameInfo.watcher == true)
		},

		officialScores() : {host: number, guest: number} {
			return currentGame.value.frame.data.host.score, currentGame.value.frame.data.guest.score
		},

		userIsHost() : boolean {
			return (this.gameConf.host.id == user.value.id)
		},
		userIsGuest() : boolean {
			return (this.gameConf.host.id != user.value.id)
		},
		hostWon() : boolean {
			return (this.score.host == 10)
		},
		guestWon() : boolean {
			return (this.score.guest == 10)
		},
		userWon() : boolean {
			return (this.userIsHost && this.hostWon) || (this.userIsGuest && this.guestWon) 
		},
		userLost() : boolean {
			return (!this.userWon)
		},
		gameState(): 'Start' | 'Play' | 'Pause' | 'End' {
			return (
				this.paused ? 'Pause' : 
				this.gameStatus == 'end' ? 'End' :
				this.start ? 'Play' :  
				'Start');
		},
		AbsPaddleHost() : {x: number, y: number} {
			return ({
				x : this.gameConf.host.paddlePos.x, 
				y : this.gameConf.host.paddlePos.y + (+this.hostPaddleDis), // * (this.canvas?.height || 0))
			})
		},
		AbsPaddleGuest() : {x: number, y: number} {
			return ({
				x : this.gameConf.guest.paddlePos.x, 
				y : this.gameConf.guest.paddlePos.y + (+this.guestPaddleDis), // * (this.canvas?.height || 0))
			})
		},
		AbsBall() : {x: number, y: number} {
			return ({
				x : this.gameConf.ball.start.x + (this.ballDisX), // * (this.canvas?.width || 0), 
				y : this.gameConf.ball.start.y + (this.ballDisY), // * (this.canvas?.height || 0),
			})
		},
	},
	methods: {
		exitGame(){
			if (debug) console.log('| CanvasGame | methods | exitGame()')
			playerStore.exitGame()
		},
		onLeaving(){
			if (debug) console.log('| CanvasGame | methods | onLeaving()')
			if (currentGame.value.endReason == 'undefined' && currentGame.value.gameInfo.hostID)
				this.exitGame()
			playerStore.resetGame()
		},

		canvasSetup() {
			if (debug) console.log('| CanvasGame | methods | canvasSetup()')
			this.canvas_old_width = this.canvas?.width || 0;
			this.canvas_old_height = this.canvas?.height || 0;
			this.canvas = this.$refs.canvas as HTMLCanvasElement;
			this.canvas.width	=  window.innerWidth - window.innerWidth * 50 / 100;
			this.canvas.height	= window.innerHeight - window.innerHeight * 50 / 100;
			this.ccontext = this.canvas?.getContext("2d") as CanvasRenderingContext2D;


			if (this.canvas_old_width)
				this.ballDisX = this.ballDisX * (this.canvas?.width || 0) / this.canvas_old_width;
			if (this.canvas_old_height)
				this.ballDisY = this.ballDisY * (this.canvas?.height || 0) / this.canvas_old_height;
			
			// setting sizes
			this.gameConf.host.paddleWidth	= this.gameConf.guest.paddleWidth	= this.canvas.width * 2 / 100;
			this.gameConf.host.paddleHeight	= this.gameConf.guest.paddleHeight	= this.canvas.height * 20 / 100;
			this.gameConf.ball.radius		= this.canvas.height / 64;
			//pitch
			this.gameConf.pitchLineWidth	= this.gameConf.host.paddleWidth /10;
			this.gameConf.pitchCircleRadius = this.canvas.height / 8;
			this.gameConf.pitchCirclePos	= {x: this.canvas.width / 2, y: this.canvas.height / 2};
			// setting positions
			this.gameConf.host.paddlePos	= {x: 0, y: this.canvas.height / 2 - this.gameConf.host.paddleHeight / 2};
			this.gameConf.guest.paddlePos	= {x: this.canvas.width - this.gameConf.guest.paddleWidth, y: this.canvas.height / 2 - this.gameConf.guest.paddleHeight / 2 }
			// TODO bug when start on edge
			// this.gameConf.ball.start		= {x: this.canvas.width , y: this.canvas.height };
			this.gameConf.ball.start		= {x: Math.random() * this.canvas.width, y: Math.random() * this.canvas.height };
		},

		drawOnCanvas() {
			// clearing canvas
			if (null != this.ccontext && null != this.canvas) {
				this.ccontext.fillStyle = "white";
				this.ccontext.fillRect(0, 0, this.canvas.width, this.canvas.height);
				this.ccontext.fillStyle = "black";
				// drawing paddles
				this.ccontext.fillRect(this.AbsPaddleHost.x, this.AbsPaddleHost.y, this.gameConf.host.paddleWidth, this.gameConf.host.paddleHeight);
				this.ccontext.fillRect(this.AbsPaddleGuest.x, this.AbsPaddleGuest.y, this.gameConf.guest.paddleWidth, this.gameConf.guest.paddleHeight);
				// drawing pitch
				this.ccontext.beginPath();
				this.ccontext.moveTo(this.canvas?.width / 2, 0)
				this.ccontext.lineTo(this.canvas?.width / 2, this.canvas?.height)
				this.ccontext.stroke();
				this.ccontext.beginPath();
				this.ccontext.arc(
					this.gameConf.pitchCirclePos.x, this.gameConf.pitchCirclePos.y,
					this.gameConf.pitchCircleRadius,
					0, 2 * Math.PI
				);
				this.ccontext.stroke();
				// drawing ball
				this.ccontext.beginPath();
				this.ccontext.arc(this.AbsBall.x, this.AbsBall.y, this.gameConf.ball.radius, 0, 2 * Math.PI);
				this.ccontext.fillStyle = this.gameConf.ball.color;
				this.ccontext.fill();
				this.ccontext.stroke();
			}
		},

		onResize() {
			this.canvasSetup();
			this.drawOnCanvas();
		},

		// keyboard event listeners
		onKeyDown(event: KeyboardEvent) {
			event.preventDefault();
			this.keyState.set(event.key, true);
			if (event.key == ' ')
				this.paused = !this.paused
		},
		onKeyUp(event: KeyboardEvent) {
			event.preventDefault();
			this.keyState.set(event.key, false);
		},

		getDeltaTime() {
			const now : number = performance.now();
			this.gameTime.deltaTime = (now - this.gameTime.lastTimeStamp);

			if (this.gameState == 'Play')
				this.gameTime.clock += this.gameTime.deltaTime;
			if (this.gameState == 'Pause')
				this.gameTime.pause += this.gameTime.deltaTime;

			this.gameTime.lastTimeStamp = now;
		},

		// testing ok, speedFactor could be a bonus, step to be reviewed if we need to change it with this.deltaTime ???
		movePaddle() {
			const step : number = this.gameTime.deltaTime * this.gameConf.ball.speedFactor

			if (this.keyState.get('ArrowUp') === true) {
				if (this.userIsHost) {
					if (this.AbsPaddleHost.y - step > 0)
						this.hostPaddleDis -= step;
				} else {
					if (this.AbsPaddleGuest.y - step > 0)
						this.guestPaddleDis -= step;
				}
				if (debug) console.log('ArrowUp')
				if (debug) console.log('paddle step : ' + step)
				if (debug) console.log('AbsPaddleHost : ' + this.AbsPaddleHost.y)

			}
			if (this.keyState.get('ArrowDown') === true) {
				if (this.userIsHost) {
					if (this.AbsPaddleHost.y + this.gameConf.host.paddleHeight + step < (this.canvas?.height || 0))
						this.hostPaddleDis += step;
				} else {
					if (this.AbsPaddleGuest.y + this.gameConf.host.paddleHeight + step < (this.canvas?.height || 0))
						this.guestPaddleDis += step;
				}
				if (debug) console.log('ArrowDown')
				if (debug) console.log('paddle step : ' + step)
				if (debug) console.log('AbsPaddleHost : ' + this.AbsPaddleHost.y)
			}
		},

		// TODO : resize amd angles
		moveBall() {
			// before step 100/15
			// const step = 100/15
			const step : number = this.gameTime.deltaTime * this.gameConf.ball.speedFactor

			if (this.gameConf.ball.start.x + this.ballDisX + this.gameConf.ball.radius  > (this.canvas?.width || 0)
			|| this.gameConf.ball.start.x + this.ballDisX - this.gameConf.ball.radius < 0)
			{
				this.ballDirX *= -1;//Math.random() * -1;
			}

			if (this.gameConf.ball.start.y + this.ballDisY  + this.gameConf.ball.radius  > (this.canvas?.height || 0)
			|| this.gameConf.ball.start.y + this.ballDisY - this.gameConf.ball.radius < 0){
				this.ballDirY *= -1;//Math.random() * -1;
			}

				
			if (this.ballDirX == 1){
				this.ballDisX += step;
			}
			else{
				this.ballDisX -= step;
			}
			if (this.ballDirY == 1)
			{
				this.ballDisY += step;
			}
			else
			{
				this.ballDisY -= step;
			}
		},

		gameLoop() {
			if (this.gameState == 'Play' ||  this.gameState == 'Pause')
				this.getDeltaTime();

			if (this.gameState == 'Play'){
				this.movePaddle();
				this.moveBall();
				this.drawOnCanvas();				
			}
			requestAnimationFrame(this.gameLoop);
		},

		// TODO
		countDown() {
			if (this.gameState == 'Start' && this.ccontext){
				for (let i = 3; i > 0; i--){
					this.ccontext.fillStyle = "white";
					this.ccontext.fillRect(0, 0, (this.canvas?.width || 0), (this.canvas?.height || 0));
					this.ccontext.fillStyle = "black";
					this.ccontext.beginPath();
					this.ccontext.fillText(i.toString(), (this.canvas?.width || 0) / 2, (this.canvas?.height || 0) / 2);
					this.ccontext?.stroke();
					if (debug) console.log(i)
					setTimeout(() => {
					}, 100000);					
				}
				this.startGame()
			}
		},



		startGame(){ // launching the clock changes the gameState and starts the game
			this.gameTime.start = performance.now()
			setTimeout(() => {
				this.gameTime.clock = performance.now() - this.gameTime.start 
				this.gameTime.lastTimeStamp = performance.now()
				this.start = true
			}, 1)
		},

		pauseGame(){

		},
		unPauseGame(){
		},

	},
	mounted() {
		if (debug) console.log('| CanvasGame | mounted()')
		window.addEventListener('beforeunload', this.onLeaving);

		window.addEventListener('keydown', this.onKeyDown);
		window.addEventListener('keyup', this.onKeyUp);
		window.addEventListener('resize', this.onResize);
	},
	beforeUnmount() {
		if (debug) console.log('| CanvasGame | beforeUnmount()')
		window.removeEventListener('keydown', this.onKeyDown);
		window.removeEventListener('keyup', this.onKeyUp);
		window.removeEventListener('resize', this.onResize);
		this.onLeaving()
		window.removeEventListener('beforeunload', this.onLeaving);
	},

	beforeRouteLeave() {
		if (debug) console.log('| CanvasGame | beforeRouteLeave()')
		this.onLeaving()
	},

	unmounted() {
		if (debug) console.log('| CanvasGame | unmounted()')
	},
}
</script>
  


<template>
	<v-card
		v-if="gameStatus == 'building' || gameStatus == 'playing'"
		class="component justify-center align-center"
		style="display: flex; flex-direction: column;" 
	>
		<v-card-item class="mt-5 justify-end w-100" style="font-weight: bold; font-size: large;">
			<v-btn
				v-show="(gameState == 'Play' || gameState == 'Pause')"
				@click="paused = !paused" 
				class="rounded-pill"
				flat
				variant="text"
				:prepend-icon="paused ? 'mdi-pause' : 'mdi-play'"
				:text="paused ? 'paused' : 'currently live'"
			></v-btn>
			<v-chip size="large">
				{{ String(gameTime.getMinutes(gameTime.clock)).padStart(2, '0') }}:{{ String(gameTime.getSeconds(gameTime.clock)).padStart(2, '0') }}
			</v-chip>
		</v-card-item>

		<v-card class="w-100" flat style="display: flex; flex-direction: row;">
			<v-card flat class="w-50 justify-center text-overline ma-0">
				<v-card-item class=" py-0 justify-center " style="font-weight: bolder; font-size: larger; background-color: lavender;">
					Host
				</v-card-item>
				<v-card class=" w-100" flat style="display: flex; flex-direction: row;">
					<v-card-item class=" justify-center w-50" :prepend-avatar="host.avatar">
						{{ host.username }}
					</v-card-item>
					<v-card-item class=" justify-center w-50">
						<v-chip class="my-2 text-h6 font-weight-bold" variant="tonal" :color="officialScores.host > officialScores.guest ? 'success' : officialScores.host === officialScores.guest ? 'primary' : 'error'">
						{{ officialScores.host }}</v-chip>
					</v-card-item>				
				</v-card>				
			</v-card>
			<v-card flat class="w-50 justify-center text-overline ma-0">
				<v-card-item class="py-0 justify-center" style="font-weight: bolder; font-size: larger;background-color: lightgoldenrodyellow;">
					Guest
				</v-card-item>
				<v-card class="w-100" flat style="display: flex; flex-direction: row;">
					<v-card-item class=" justify-center w-50 ">
						<v-chip class="my-2 text-h6 font-weight-bold" variant="tonal" :color="officialScores.guest > officialScores.host ? 'success' : officialScores.guest === officialScores.host ? 'primary' : 'error'">
						{{ officialScores.guest }}</v-chip>
					</v-card-item>				
					<v-card-item class=" justify-center w-50" :append-avatar="guest.avatar">
						{{ guest.username }}
					</v-card-item>
				</v-card>				
			</v-card>
		</v-card>

		<!-- <canvas id="CanvasGame" ref="canvas" width="800" height="500" style="border:1px solid black;"></canvas> -->

		<v-card height="500" width="800" class="border">CANVAS</v-card>

		<v-card
			style="display: flex; flex-direction: row;"
			class="w-100 -5 justify-center"
			flat
		>
			<v-btn
				v-show="(gameState == 'Play' || gameState == 'Pause')"
				color="primary"
				variant="elevated"
				size="x-large"
				class="ma-2"
				@click="paused = !paused" 
			>
				{{ paused? 'Unpause game ' : 'Pause game '  }}
			</v-btn>

			<v-btn
				v-show="gameState == 'Start'"
				color="primary"
				variant="elevated"
				size="x-large"
				class="ma-2"
				@click="startGame" 
			> Start Game !
			</v-btn>

			<v-btn
				color="primary"
				variant="tonal"
				size="x-large"
				class="ma-2"
				@click="exitGame" 
			> Exit Game
			</v-btn>
		</v-card>

		<v-card :width="canvas?.width" style="display: flex; flex-direction: row;" class="ma-0 pa-0" flat>
			<v-card class="pa-1 ma-1 w-50">
				<h2>| BALL |</h2>
				<p>| ball  abs | x : {{ Math.round(AbsBall.x) }}, y : {{ Math.round(AbsBall.y) }}</p>
				<p>| ball  start | x : {{ Math.round(gameConf.ball.start.x) }}, y : {{ Math.round(gameConf.ball.start.y) }}</p>
				<p>| ball  radius | {{ Math.round(gameConf.ball.radius) }}</p>
				<p>| ball  ballDis | x : {{Math.round(ballDisX)}}, y : {{ Math.round(ballDisY) }}</p>
				<p>| ball  ballDir | x : {{ballDirX}}, y : {{ ballDirY }} </p>
				<h2>| PADDLE |</h2>
				<p>| host  | dim (w : {{ Math.round(gameConf.host.paddleWidth) }}, h : {{ Math.round(gameConf.host.paddleHeight) }})</p>
				<p>| host  | abs (x : {{ Math.round(AbsPaddleHost.x) }}, y : {{ Math.round(AbsPaddleHost.y) }}) | start (x : {{ Math.round(gameConf.host.paddlePos.x) }}, y : {{ Math.round(gameConf.host.paddlePos.y) }}) | dis (y : {{ Math.round(hostPaddleDis) }})</p>
				<p>| guest  | dim (w : {{ Math.round(gameConf.guest.paddleWidth) }}, h : {{ Math.round(gameConf.guest.paddleHeight) }})</p>
				<p>| guest  | abs (x : {{ Math.round(AbsPaddleGuest.x) }}, y : {{ Math.round(AbsPaddleGuest.y) }}) | start (x : {{ Math.round(gameConf.guest.paddlePos.x) }}, y : {{ Math.round(gameConf.guest.paddlePos.y) }}) | dis (y : {{ Math.round(guestPaddleDis) }})</p>


			</v-card>		
			<v-card class="pa-1 ma-1 w-50">
				<h2>| CONF |</h2>
				<p>| canvas |  width : {{ canvas?.width }} | height : {{ canvas?.height }}</p>
				<p>| host | {{ gameConf.host.id }}</p>
				<p>| guest | {{ gameConf.guest.id }}</p>
				<h2>| GAME STATE : {{ gameState }}</h2>
				<p>| deltaTime |  {{ Math.round(gameTime.deltaTime) }} | </p>
				<p>| lastTimeStamp |  {{ Math.round(gameTime.lastTimeStamp) }} | </p>
				
				<p>Game: {{ String(gameTime.getMinutes(gameTime.clock)).padStart(2, '0') }}:{{ String(gameTime.getSeconds(gameTime.clock)).padStart(2, '0') }}</p>
				<p>Paused: {{ String(gameTime.getMinutes(gameTime.pause)).padStart(2, '0') }}:{{ String(gameTime.getSeconds(gameTime.pause)).padStart(2, '0') }}</p>
				<p>Total: {{ String(gameTime.getMinutes(gameTime.clock + gameTime.pause)).padStart(2, '0') }}:{{ String(gameTime.getSeconds(gameTime.clock + gameTime.pause)).padStart(2, '0') }}</p>

			</v-card>
		</v-card>

</v-card>



</template>

<style scoped>
.component {
	max-width:  100%;
	max-height:  100%;
	width: fit-content;
}

</style>
