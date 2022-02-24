/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:59:51 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/23 16:59:51 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASICS_H
# define BASICS_H

# include "../my_lib/libft/libft.h"
# include <stdio.h>

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_panel
{
	void		*pointer;
	char		*pixels;
	t_vector	size;
	int			bpp;
	int			line_size;
	int			endian;
}	t_panel;

int		error(char *message);
void	*null_error(char *message);
void	print_warning(char *message);

#endif
