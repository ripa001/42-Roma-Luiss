/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.dto.ts                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:04:04 by mmarinel          #+#    #+#             */
/*   Updated: 2023/11/24 19:33:07 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

export class PaddleDto {
	public w: number;
	public h: number;
	public x: number;
	public y: number;
	public color: string;
}

export class BallDto {
	public radius: number;
	public x: number;
	public y: number;
	public dx: number;
	public dy: number;
	public color: string;
}

export class PlayerData {
	paddle: PaddleDto
	score: number
}

export class FrameData {
	ball: BallDto
	host: PlayerData
	guest: PlayerData
}

export class FrameDto {
	hostID: number
	guestID: number
	seq: number
	data: FrameData
}
