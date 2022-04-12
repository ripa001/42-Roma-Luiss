/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:07:29 by ebassi            #+#    #+#             */
/*   Updated: 2022/04/12 23:56:56 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
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

typedef enum s_redirect {
	RE_GREAT = 1,
	RE_DOUBLE_GREAT = 2,
	RE_LESS = 3,
	PIPE = 4
}	t_redirect;

typedef struct s_tok {
	int				type;
	char			*data;
	int				id;
	int				exit;
	struct s_tok	*next;
}	t_tok;

void	signal_handler(int sig);
void	get_pwd();
char	*set_prompt();
void	get_next_lst(t_tok *input_ln);
void	init(t_tok *x);
void 	print_list(t_tok *x);
void	change_dir(t_tok *input_ln);
void	exit_command();
void	ft_echo(t_tok *input_ln);

#endif