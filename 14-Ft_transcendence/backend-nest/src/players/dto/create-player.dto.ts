/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create-player.dto.ts                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:18:53 by earendil          #+#    #+#             */
/*   Updated: 2023/10/12 14:27:35 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// import { IsNotEmpty, IsNumber } from 'class-validator';
import { ApiProperty } from '@nestjs/swagger';

export class CreatePlayerDto {
	@ApiProperty()
	id: number;
	@ApiProperty()
	username: string;
	@ApiProperty()
	avatar: string;

	@ApiProperty()
	firstName?: string;
	@ApiProperty()
	lastName?: string;
	@ApiProperty()
	profileIntra?: string;
}
