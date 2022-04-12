/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:06:44 by ebassi            #+#    #+#             */
/*   Updated: 2022/04/13 00:31:58 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_op(t_tok *input_ln, char *op)
{
	input_ln->type = 1;
	input_ln->data = op;
	input_ln->data = ft_strtrim(input_ln->data, " ");
	input_ln->exit = 0;
}

int error(char *str)
{
	ft_putendl_fd(str, 1);
	return (0);
}

int double_check(char a, char b)
{
	if (a == b)
	{
		if (a == '&')
			return (2);
		else
			return (1);
	}
	return (0);
}

void	get_command(t_tok *input_ln, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	input_ln->id = 0;
	while (line[i])
	{
		if (line[i] == '|' || line[i] == '>' || line[i] == '<' || (line[i] == '&' && line[i + 1] == '&'))
		{
			get_next_lst(input_ln);
			input_ln = input_ln->next;
			if (line[i] == line[i + 1])
			{
				printf("%c ", line[i]);
				handle_op(input_ln, ft_substr(line, i, 2));
				get_next_lst(input_ln);
				input_ln = input_ln->next;
				j = i + 2;
				i++;
			}
			else
			{
				handle_op(input_ln, ft_substr(line, i, 1));
				get_next_lst(input_ln);
				input_ln = input_ln->next;
				j = i + 1;
			}
		}
		input_ln->type = 0;
		input_ln->data = ft_substr(line, j, i - j + 1);
		input_ln->data = ft_strtrim(input_ln->data, " ");
		input_ln->exit = 0;
		i++;
	}
	input_ln->next = 0;
}

int		ft_find(char **builtin, char *str)
{
	int	i;

	i = 0;
	while (builtin[i])
	{
		if (!(ft_strncmp(str, builtin[i], ft_strlen(str))))
			return (1);
		i++;
	}
	return (0);
}

// void	exec_cmd(char *str)
// {
// 	execve(path, args, param->envp)
// }

void	handle_cmd(t_tok *input_ln)
{
	int		i;
	char	*str;
	char	**builtin;

	i = 0;
	str = 0;
	builtin = ft_split("cd echo env exit export pwd unset", ' ');
	while (input_ln)
	{
		i = 0;
		while (1)
		{
			if (input_ln->data[i] == ' ' || !input_ln->data[i])
			{
				str = ft_substr(input_ln->data, 0, i);
				if (ft_find(builtin, str))
				{
					if (!(ft_strncmp(str, "pwd", 3)))
						get_pwd();
					if (!(ft_strncmp(str, "cd", 2)))
						change_dir(input_ln);
					if (!(ft_strncmp(str, "echo", 4)))
						get_pwd();
					if (!(ft_strncmp(str, "env", 3)))
						get_pwd();
					if (!(ft_strncmp(str, "exit", 4)))
						exit_command();
					if (!(ft_strncmp(str, "export", 6)))
						get_pwd();
					if (!(ft_strncmp(str, "unset", 5)))
						get_pwd();
				}
				// exec_cmd(str);

				break;
			}
			i++;
		}
		input_ln = input_ln->next;
	}
}

void	init_mini(char *envp[])
{
	(void)envp;
	t_tok	input_ln;
	char	*command;
	char	*line;
	char	*str;

	line = 0;
	command = 0;
	/*----------------------DA DECOMMENTARE-----------------------*/
	// signal(SIGINT, signal_handler);
	// signal(SIGQUIT, signal_handler);
	// signal(SIGTSTP, signal_handler);
	while (42)
	{
		init(&input_ln);
		str = set_prompt();
		line = readline(str);
		if (line)
		{
			add_history(line);
			get_command(&input_ln, line);
			handle_cmd(&input_ln);
			print_list(&input_ln);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	init_mini(envp);
	return (0);
}