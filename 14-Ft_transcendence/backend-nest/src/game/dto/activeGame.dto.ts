/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activeGame.dto.ts                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:48:39 by mmarinel          #+#    #+#             */
/*   Updated: 2023/11/26 12:37:39 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

import { CustomizationOptions } from "./customization.dto"

export class ActiveGameDto
{
	roomId: string
	hostID: number
	guestID: number
	customization: CustomizationOptions
};
