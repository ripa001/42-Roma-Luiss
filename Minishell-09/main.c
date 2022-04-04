/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:10:51 by dripanuc          #+#    #+#             */
/*   Updated: 2022/04/04 18:43:50 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_prompt()
{
	write(1, GREEN, ft_strlen(GREEN));
	write(1, "Minishell $ ", 12);
	write(1, GREEN, ft_strlen(GREEN));
}

int	get_command(t_minishell *shell, char *line)
{
	int i;
	static int j;
	char *command;

	j = 0;
	i = ft_index_strchr(line, ' ');
	printf("%s-%i",line, i);
	command = ft_substr(line, j, i);
	printf("command %s",command);
	getcwd(shell->position, sizeof(shell->position));
	printf("c %s",command);
	if (!ft_strncmp(command, "pwd", ft_strlen(command)))
		printf("\n%s", shell->position);
	return (1);
}

int	init_shell(t_minishell *shell)
{
	char *line;

	while (1)
	{
		my_prompt();
		line = readline("");
		if (line)
		{
			get_command(shell, line);
		}
	}
}

int	main()
{
	t_minishell shell;

	init_shell(&shell);
}