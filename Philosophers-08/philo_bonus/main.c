/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:48:14 by dripanuc          #+#    #+#             */
/*   Updated: 2022/04/02 03:17:55 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	my_sleep(long long time, t_philosophers *philo)
{
	long long	i;

	i = time_function();
	while (!(philo->dead))
	{
		if (time_function() - i >= time)
			break ;
		usleep(50);
	}
}

void	my_eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_mutex("has taken a fork", philo);
	sem_wait(philo->data->forks);
	print_mutex("has taken a fork", philo);
	print_mutex("is eating", philo);
	sem_wait(philo->data->is_eating);
	philo->eat = 1;
	if (++philo->n_eating == philo->data->n_e)
		if (++philo->data->n_finished == philo->data->n)
			my_exit(1, "Tutti i filosofi hanno finito di mangiare");
	philo->lm = get_time() - philo->data->time;
	sem_post(philo->data->is_eating);
	my_sleep(philo->data->time_eat, philo->data);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	philo->eat = 0;
}

void	end_success(t_philosophers *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n)
		free(philo->philos[i]);
	free(philo->philos);
	exit(1);
}

void	end(t_philosophers *philo)
{
	int	i;
	int	ret;

	i = 0;
	while (i < philo->n)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < philo->n)
				kill(philo->philos[i]->pid, SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(philo->forks);
	sem_close(philo->message);
	sem_close(philo->is_eating);
	sem_unlink("sem_forks");
	sem_unlink("sem_message");
	sem_unlink("sem_eating");
	end_success(philo);
}

int	main(int argc, char *argv[])
{
	t_philosophers	philo;
	int				i;

	i = 0;
	while (++i < argc)
		if (!ft_strisdigit(argv[i]))
			my_exit(0, "Non sono previsti argomenti alfanumerici");
	init_philosophers(argv, &philo, argc);
	i = -1;
	while (++i < philo.n)
	{
		philo.philos[i]->pid = fork();
		if (philo.philos[i]->pid < 0)
			return (my_exit(0, "Error while forking!\n"));
		if (!philo.philos[i]->pid)
			philo_loop(philo.philos[i]);
	}
	end(&philo);
	return (1);
}
