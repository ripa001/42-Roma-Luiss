/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:56:27 by mpatrini          #+#    #+#             */
/*   Updated: 2022/06/04 01:16:53 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <fcntl.h>

# define BUFFER_SIZE 1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

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
	int		sp;
	int		hash;
	int		is_neg;
	int		fd;
	char	*str;
}	t_print;

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *c);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
int			ft_tolower(int c);
int			ft_toupper(int c);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *s, int c);
int			ft_strchr_int(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
void		ft_putendl_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_itoa(int n);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char		*ft_ret_line(char *line);
char		*ft_modify_line(char *line);
char		*get_next_line(int fd);
char		*ft_strjoin_get(char *s1, char *s2);
char		*ft_substr_get(char *s, unsigned int start, size_t len);
int			ft_strlen_get(char *c);
char		*ft_strdup_get(char *s1);
int			ft_printf(const char *format, ...);
int			ft_print_char(t_print *tab, const char *f, int i);
int			ft_format(t_print *tab, const char *f, int i);
int			ft_find_prc(t_print *tab, const char *f, int i);
int			ft_find_wdt(t_print *tab, const char *f, int i);
t_print		*ft_clear_tab(t_print *tab);
t_print		*ft_initialise_tab(int fd, t_print *tab);
int			ft_itoa_len(unsigned int n);
int			ft_itoa_len2(size_t n);
char		*ft_utoa(unsigned int n);
char		*ft_hex_long_itoa(size_t n, const char *base);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_substr_free(char *s, unsigned int start, size_t len);
char		*ft_hex_itoa(unsigned int n, const char *base);
void		ft_s(t_print *tab);
void		ft_di(t_print *tab);
void		ft_print_str(t_print *tab, char *a);
void		ft_c(t_print *tab);
void		ft_p(t_print *tab);
void		ft_x_up(t_print *tab);
void		ft_x(t_print *tab);
void		ft_u(t_print *tab);
char		*ft_prc_x(t_print *tab, char *a, int i);
char		*ft_hash(t_print *tab, char *a, int is_upper, int i);
char		*ft_num_sign(t_print *tab, char *i);
char		*ft_di_wdt(t_print *tab, char *i, int c, int flag);
char		*ft_di_prc(t_print *tab, char *i, int a);
char		*ft_u_prc(t_print *tab, char *i, unsigned int a);
char		*ft_u_wdt(t_print *tab, char *i, int c, int flag);
long long	ft_atoi_long(const char *str);
void		ft_exit_error(char *error);
int			ft_strlen_matrix(char **matrix);
void		ft_free_matrix(char **matrix);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_abs(int num);
void		ft_free_lst(t_list *moves);
int			ft_printfd(int fd, const char *format, ...);
t_print		*ft_initialise_stab(t_print *tab);
int			ft_sprint_char(t_print *tab, const char *f, int i);
char		*ft_sprintf(const char *format, ...);
int			ft_sprint_char(t_print *tab, const char *f, int i);
void		ft_ss(t_print *tab);
void		ft_sdi(t_print *tab);
void		ft_sprint_str(t_print *tab, char *a);
void		ft_sc(t_print *tab);
void		ft_sp(t_print *tab);
void		ft_sx_up(t_print *tab);
void		ft_sx(t_print *tab);
void		ft_su(t_print *tab);
void		ft_add_char(t_print *tab, char c);

#endif
