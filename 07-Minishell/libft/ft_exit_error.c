/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini@student.42roma.it <mpatrini>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 03:27:17 by mpatrini@st       #+#    #+#             */
/*   Updated: 2022/02/21 03:31:50 by mpatrini@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit_error(char *error)
{
	write(1, error, ft_strlen(error));
	exit(EXIT_FAILURE);
}
