/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:20:54 by dripanuc          #+#    #+#             */
/*   Updated: 2022/04/02 03:18:31 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_philosophers	philo;
	int				i;

	i = 0;
	while (++i < argc)
		if (!ft_strisdigit(argv[i]))
			my_exit(0, "Non sono previsti argomenti alfanumerici");
	init_philosophers(argv, &philo, argc);
	end_success(&philo);
}
