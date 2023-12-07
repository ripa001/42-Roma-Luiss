/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create-game.dto.ts                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:04:02 by mmarinel          #+#    #+#             */
/*   Updated: 2023/11/19 13:13:44 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

export class CreateGameDto {
	hostID: number
	guestID: number

	watcher: boolean
}
