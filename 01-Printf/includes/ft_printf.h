/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:36:08 by dripanuc          #+#    #+#             */
/*   Updated: 2022/01/23 01:29:44 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_print
{
	va_list	args;
	int		wdt;
	int		prc;
	int		zero;
	int		pnt;
	int		dash;
	int		tl;
	int		sign;
	int		is_zero;
	int		perc;
	int		hash;
	int		is_neg;
	int		sp;
}	t_print;

int		ft_printf(const char *s, ...);
void	ft_print_str(t_print *tab, char *a);
char	*ft_hash(t_print *tab, char *a, char is_upper, int i);
void	ft_c(t_print *params);
void	ft_di(t_print *params);
void	ft_x(t_print *params, char c);
void	ft_u(t_print *params);
void	ft_p(t_print *params);
void	ft_s(t_print *params);
void	get_flag(t_print *params, char *c);
int		check_set(char c, char *set);
void	check_format(char *c, t_print *params);
char	*check_flag(t_print *params, char *c, int *n);
char	*ft_find_prc(t_print *tab, char *f, int *n);
char	*ft_wdt_x(t_print *tab, char *a, int flag);
char	*ft_find_wdt(t_print *tab, char *f);
char	*ft_u_wdt(t_print *tab, char *i, int c, int flag);
char	*ft_u_prc(t_print *tab, char *i, unsigned int a);
char	*ft_di_wdt(t_print *tab, char *i, int c, int flag);
char	*ft_di_prc(t_print *tab, char *i, int a);
char	*ft_prc_x(t_print *tab, char *a, int i);
char	*ft_num_sign(t_print *tab, char *i);
char	*ft_utoa(unsigned int n);
int		ft_itoa_len(unsigned int n);
int		ft_itoa_len2(size_t n);
char	*ft_hex_long_itoa(size_t n, const char *base);
char	*ft_hex_itoa(unsigned int n, const char *base);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_substr_free(char *s, unsigned int start, size_t len);
t_print	*ft_reset_tab(t_print *tab);
t_print	*ft_initialise_tab(t_print *tab);

#endif