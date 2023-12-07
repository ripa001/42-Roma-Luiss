/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth.guard.jwt.ts                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:12:58 by earendil          #+#    #+#             */
/*   Updated: 2023/10/17 16:58:08 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

import { CanActivate, ExecutionContext, Injectable } from '@nestjs/common';
import { Reflector } from '@nestjs/core';
import { JwtService } from '@nestjs/jwt';
import { Request } from 'express';
import { IS_PUBLIC_ENDPOINT } from '../decorators/auth.public.decorator';
import { PlayersService } from 'src/players/players.service';
import { IS_PROTECTED_ENDPOINT } from '../decorators/auth.protected.decorator';
import { AuthService } from '../auth.service';

export type JwtPayload = {
	sub: string;
};

@Injectable()
export class JwtAuthGuard implements CanActivate {
	constructor(
		private readonly jwtService: JwtService,
		private readonly pservice: PlayersService,
		private readonly reflector: Reflector,
		private readonly authService: AuthService
	) {}

	async canActivate(context: ExecutionContext): Promise<boolean> {
		// class-level metadata affects all the methods of that class
		// So, the metadata bound to a method is the metadata bound to the class
		// and the specific method metadata
		// So, we need to provide both context and nest will use the most specific one.
		const isPublicEndpoint = this.reflector.getAllAndOverride<boolean>(
			IS_PUBLIC_ENDPOINT,
			[context.getClass(), context.getHandler()],
		);
		const isProtectedEndpoint = this.reflector.getAllAndOverride<boolean>(
			IS_PROTECTED_ENDPOINT,
			[context.getClass(), context.getHandler()],
		);

		if (isPublicEndpoint) return true;

		const request = context.switchToHttp().getRequest();
		const token = this.extractTokenFromHeader(request);
		if (!token) {
			return false;
		}
		try {
			const payload = await this.jwtService.verifyAsync(token, {
				secret: process.env.JWT_SECRET,
			});
			// 💡 We're assigning the payload to the request object here
			// so that we can access it in our route handlers
			request['user'] = payload;
			if (false === this.pservice.isLoggedIn(Number(payload.sub))) {
				// if backend was unavailable for a period of time, all connections are now lost
				if (false == (await this.authService.is2FAset(Number(request.user.sub)))) {
					this.pservice.addConnection(Number(request.user.sub));
					return true;
				}
				else if (isProtectedEndpoint) return true;
				else return false;
			}
			return true;
		} catch {
			return false;
		}
	}

	private extractTokenFromHeader(request: Request): string | undefined {
		const [type, token] = request.headers.authorization?.split(' ') ?? [];
		return type === 'Bearer' ? token : undefined;
	}
}
