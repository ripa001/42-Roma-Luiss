/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth.controller.ts                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:49:41 by earendil          #+#    #+#             */
/*   Updated: 2023/12/02 17:08:11 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

import {
	Body,
	Controller,
	Delete,
	Get,
	InternalServerErrorException,
	Post,
	Redirect,
	Request,
	UnauthorizedException,
	UseGuards,
} from '@nestjs/common';
import { AuthService } from './auth.service';
import { FortyTwoAuthGuard } from './guards/auth.guard.42';
import { PlayersService } from 'src/players/players.service';
import { Public } from './decorators/auth.public.decorator';
import { Protected } from './decorators/auth.protected.decorator';
import { GameGateway } from 'src/game/game.gateway';

const debug = true

@Controller('auth')
export class AuthController {
	constructor(
		private readonly authService: AuthService,
		private readonly pservice: PlayersService,
		private readonly gGateway: GameGateway
	) {}

	/**
	 * this endpoint is to be called during oauth login through 42 API. It is both starting endpoint and callback url.
	 * @param req
	 * @returns
	 */
	@Public()
	@UseGuards(FortyTwoAuthGuard) //OAUTH guard, not jwt
	@Redirect('', 302)
	@Get('42')
	async login42(@Request() req) {
		const userID = Number(req.user.id);

		try {
            if (debug) console.log('DEBUG | Auth.controller | login42() : called');

			// after validate(), user is stored in req.user
			// now let's sign in the app (find/register user, create a token)
			const token = await this.authService.signIn(req.user);

			//to prevent old non-deleted session to activate
			this.pservice.removeConnection(userID);
			// log the user in
			if (false == (await this.authService.is2FAset(userID))) {
				this.pservice.addConnection(userID);
				this.gGateway.broadcastPlayerStatus(userID);
			}

			// let's share the session token with the user
			const redirect_url = new URL(`${req.protocol}:${req.hostname}`);
			redirect_url.pathname = await this.authService.is2FAset(userID) ? 'login-2fa' : '';
			redirect_url.port = process.env.FRONTEND_PORT;
			redirect_url.searchParams.append('token', `${token.toString()}`);
			return { url: `${redirect_url.href}` };
		} catch (error) {
			throw new InternalServerErrorException(error);
		}
	}

	@Delete('42')
	async logOut(@Request() req): Promise<void> {
		const userID = Number(req.user.sub);

		this.pservice.removeConnection(userID);
		this.gGateway.broadcastPlayerStatus(userID);
	}

	/**
	 * this endpoint is to be called during enablement of 2fa authentication once logged in.
	 * @param req
	 * @returns
	 */
	@Get('2fa/qrcode')
	async getQRCode(@Request() req) {
		const userID = Number(req.user.sub);

		try {
			const qrcode = await this.authService.generate2FAQRCode(userID);
			return { qrcode };
		} catch (error) {
			throw new InternalServerErrorException(error);
		}
	}

	/**
	 * this endpoint is to be called during 2fa login
	 * @param otp
	 * @param req
	 */
	@Protected()
	@Post('2fa/login')
	async login2fa(@Body('otp') otp: string, @Request() req) {
		const userID = Number(req.user.sub);

		if (debug) console.log('DEBUG | Auth.controller | login2fa() | otp : ' + otp);
		if (false == (await this.authService.verifyOTP(userID, otp)))
			return false;
		this.pservice.addConnection(userID);
		this.gGateway.broadcastPlayerStatus(userID);
		return true;
	}

	/**
	 * this endpoint is to be used during enablement of 2fa authentication after generation of qr code.
	 * @param otp
	 * @param req
	 */
	@Post('2fa')
	async verify2fa(@Body('otp') otp: string, @Request() req) {
        if (debug) console.log('DEBUG | Auth.controller | verify2fa() | otp : ' + otp);
		return (await this.authService.verifyOTP(Number(req.user.sub), otp))
	}

	/**
	 * this endpoint is to be called to disable 2fa 
	 * @param otp
	 * @param req
	 */
	@Protected()//TODO REMOVE DECOAATOR
	@Post('2fa/remove')
	async remove2fa(@Body('otp') otp: string, @Request() req) {
        if (debug) console.log('DEBUG | Auth.controller | remove2fa() | otp : ' + otp);
		return (await this.authService.removeOTP(Number(req.user.sub), otp))
	}
}
