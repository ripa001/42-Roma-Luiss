/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:31:56 by dripanuc          #+#    #+#             */
/*   Updated: 2022/01/26 23:02:42 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# define BUFFER_SIZE 42

char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin_free(char const *s1, char const *s2, int size);
char	*ft_substr(char const *s, int start, int len, int free_flag);
int		ft_strlen(const char *str);
int		ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
void	funzione_while(char *s, char *sub, int len, int start);

#endif
