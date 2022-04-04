/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:23:43 by dripanuc          #+#    #+#             */
/*   Updated: 2022/04/04 18:43:57 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <errno.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <termcap.h>
# include <sys/ioctl.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define GREEN "\e[1;32m"
# define RESET "\e[0m"
# define RED "\e[1;91m"
# define CYAN "\e[1;36m"
# define YELLOW "\e[1;33m"
# define PURPLE "\e[1;35m"
# define BLUE "\e[1;34m"

typedef struct s_separator
{
	int pipe;
	int great;
	int great_great;
	int ampersand;
	int less;
	int great_ampersand;
} t_separator;

typedef struct s_commands
{
	/* data */
} t_commands;

typedef struct s_minishell
{
	char position[1000];
	t_commands	*commands;
	t_separator	*separators;
} t_minishell;


void	signal_handler(int sig);
void	get_pwd(void);
#endif
