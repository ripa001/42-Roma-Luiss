/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:07:29 by mpatrini          #+#    #+#             */
/*   Updated: 2022/06/30 16:07:27 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <termios.h>
# include <dirent.h>
# include <term.h>
# include <curses.h>
# include <termcap.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define EMPTY 0 // ' '
# define CMD 1 // C
# define ARG 2 // R
# define TRUNC 3 // T
# define APPEND 4 // A
# define INPUT 5 // I
# define HEREDOC 6 // H
# define PIPE 7 // P
# define AND 8 // N
# define OR 9 // O
# define PARO 10 // Z
# define PARC 11 // X
# define END 12 // E

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_tok {
	char			*str;
	int				type;
	int				lvl;
	struct s_tok	*next;
	struct s_tok	*prev;
}	t_tok;

typedef struct s_mini {
	t_tok	*start;
	int		in;
	int		out;
	int		fdin;
	int		fdout;
	int		pipin;
	int		pipout;
	int		pid;
	int		charge;
	int		parent;
	int		last;
	int		ret;
	int		exit;
	int		no_exec;
	int		lvl;
	char	**env;
}	t_mini;

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	int				read;
	pid_t			pid;
}				t_sig;

t_sig	g_sigs;

void	rl_replace_line(const char *text, int clear_undo);
int		ft_is_types2(t_tok *tok, char *types);
int		ft_is_types(t_tok *tok, char *types);
int		ft_check_cmd(t_mini *mini, t_tok *tok);
void	ft_convert_par(t_tok *start);
void	ft_free_tok(t_tok *start);
t_tok	*ft_next_tok(char *line, int *i);
void	ft_arg_type2(t_tok *tok, int sep, t_mini *mini);
void	ft_arg_type(t_tok *tok, int sep, t_mini *mini, int i);
t_tok	*ft_get_tok(char *line, t_mini *mini);
t_tok	*ft_prev_separator(t_tok *tok, int i);
t_tok	*ft_next_separator(t_tok *tok, int i);
int		ft_is_valid_arg(t_tok *tok);
void	ft_arrange_args2(t_tok *tok, t_mini *mini, t_tok *prev);
void	ft_arrange_args(t_mini *mini);
char	**ft_init_env(char **env, int k);
char	*ft_get_env(char **env, char *str);
int		ft_exec_from_system(char **cmd, t_mini *mini);
void	ft_exec_cmd2(char **cmd, t_mini *mini);
void	ft_exec_cmd(t_mini *mini, t_tok *tok);
void	ft_exec(t_mini *mini, t_tok *tok);
int		ft_find(char *str);
int		ft_exec_error(char *path);
int		ft_exec_sys2(char *path, char **cmd, t_mini *mini);
char	*ft_new_data(char *cmd, int j, int *x, char *current_env);
char	*ft_current_env2(char *cmd, int k, int *x, char *current_env);
char	*ft_current_env(t_mini *mini, char *cmd, int *x, int j);
char	*expand_envars(char *cmd, t_mini *mini);
char	*ft_env_flag(int flag, char *current_env2);
char	*ft_tilde(char *cmd, int x, t_mini *mini, int quotes);
char	*ft_env_digit(char *cmd, int *x, int j);
int		ft_ignore_sep(char *line, int i);
char	*ft_line(t_mini *mini);
void	ft_get_cmd(t_mini *mini);
void	ft_heredoc2(t_tok *tok, int fd[2]);
void	ft_heredoc(t_tok *tok, t_mini *mini);
int		ft_pipe_open(t_tok *tok);
int		ft_pipe(t_mini *mini);
void	ft_signal_handler_global(int signal);
t_tok	*ft_next_run(t_tok *tok, int i);
void	ft_mini(t_mini *mini);
void	ft_subshell(t_mini *mini, char *av);
void	ft_sub(t_mini *mini, char *str);
char	*ft_set_prompt(char **env);
int		ft_quotes(char *line, int in);
int		ft_check_quotes(t_mini *mini, char **line);
int		qquotes(char c, int q);
int		quote_in_quotes(char *line);
char	*check_readline(char *line);
void	ft_reset_fds(t_mini *mini);
void	ft_close_fds(t_mini *mini);
void	ft_reset_stds(t_mini *mini);
void	ft_redirection(t_mini *mini, t_tok *tok, int type);
void	ft_input(t_mini *mini, t_tok *tok);
int		ft_isspace(char c);
void	ft_close(int fd);
int		ft_is_type(t_tok *tok, int type);
void	ft_print_start(t_tok *start);
int		ft_is_sep(char *line, int i);
void	ft_change_dir(char **cmd, t_mini *mini);
void	ft_echo(char **cmd, t_mini *mini);
void	ft_env(t_mini *mini);
void	ft_exit_command( t_mini *mini, char **cmd);
void	ft_export_command(char **cmd, t_mini *mini);
void	ft_get_pwd(t_mini *mini);
void	ft_unset_var(t_mini *mini, char **cmd);
char	*ft_expand(char *line, t_mini *mini);
char	*ft_find_path(t_mini *mini, char *cmd);
char	**ft_convert_cmd_to_matrix(t_tok *start);
char	*ft_add_spaces(char *line, t_mini *mini);
void	ft_mini_helper(t_mini *mini);
char	**ft_copy_env(char **env);
char	*ft_replace_env(char *env, char *name, char *value);
void	ft_print_export(char **env2);
void	ft_export_alone(char **env);
char	**ft_export_command3(char **cmd, t_mini *mini, int flag, int k);
void	ft_export_command_help(t_mini *mini, char **cmd, int *k, int *j);
void	ft_export_helper(char *str, int *k, t_mini *mini);
void	ft_init_signals( void );
char	*ft_add_spaces(char *line, t_mini *mini);
char	*ft_add_spaces2(char *line, int i, int k);
char	*ft_new_alloc(char *line);
void	ft_signal_handler_global(int signal);
char	*ft_join_path(char *str, char *str2);
void	ft_mini_helper(t_mini *mini);
void	ft_main2(t_mini *mini);
char	*ft_check_dir(char *dir, char *cmd);
char	*ft_find_path(t_mini *mini, char *cmd);
int		ft_get_tok_help(char *line, int i);
char	*expand_envars_help(char *cmd, int *x, t_mini *mini, int j);
char	*ft_expand_wild(char *ret);
char	*ft_rev_split(char **matrix);
void	ft_print_tok(t_tok *start);
char	*ft_findwild_multi(char *str, char *dir);
char	**ft_find_multi(char **files, char *find, char *last);
int		ft_strcmp_end(char *name, char *end);
char	**ft_findwild_multi2(char *str, char *dir);
char	**ft_check_last(char **files, char *str, int i, int j);
char	**ft_findwild_multi3(char *str, char *dir);
char	**ft_find_files(char *dir, int i);
char	**ft_find_files3(char *dir, char *srch, int i);
int		ft_folder_size(char *dir);
int		ft_folder_size(char *dir);
char	**ft_find_files3(char *dir, char *srch, int i);
char	**ft_find_files(char *dir, int i);
char	**ft_findwild_multi3(char *str, char *dir);

#endif