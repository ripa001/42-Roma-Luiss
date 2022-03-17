/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 10:01:24 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/16 11:26:50 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct s_arrt
{
	int *arr;
	int count;
}			t_arr;

typedef	struct
{
	int	*ar_a;
	int	*ar_b;
	int	size_a;
	int	size_b;
	int	max;
	int max_pos;
	int	min;
	int	min_pos;
	int size_comb;
}				t_struct;

typedef struct s_moves
{
	int min_a;
	int min_b;
	int dir_a;
	int dir_b;
	int sum;
}				t_moves;

void	ft_swap_a(int *ar);
void	ft_swap_b(int *ar);
void	ft_swap_s(int *ara, int *arb);
void	ft_push_a(t_struct *data);
void	ft_push_b(t_struct *data);
void	ft_rotate_a(t_struct *data);
void	ft_rotate_b(t_struct *data);
void	ft_rotate_r(t_struct *data);
void	ft_rev_rotate_a(t_struct *data);
void	ft_rev_rotate_b(t_struct *data);
void	ft_rev_rotate_r(t_struct *data);
void	ft_error(void);
int		ft_order(int *ar, int size);
int		ft_check(char **matrix, int size);
int		*ft_initializer(char **matrix, int size);
int		ft_checkfordoubles(int *ar, int size);
int		*ft_ardup(int *ar, int size);
void	ft_sort_ar(int *ar, int size);
void	ft_printarray(int *ar, int size);
void	ft_swap(int	*a, int *b);
int		ft_min(int *array, int size);
int		ft_max(int *array, int size);
int		ft_findind(int nb, int *array, int size);
int		*ft_findcomb(t_struct *data);
void	ft_checkmalloc(void *ptr);

#endif