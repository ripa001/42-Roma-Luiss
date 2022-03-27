/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:48:14 by dripanuc          #+#    #+#             */
/*   Updated: 2022/03/27 20:17:52 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_loop(t_philosophers	*philo)
{
	while (!(philo->dieded))
	{

		//mutex fork id philo -1
		//mutex mess
		//un-mutex mess
		//mutex fork2 id philo
		//mutex mess
		//un-mutex mess
		// eating
		//mutex mess
		//un-mutex mess
		//think
		//sleep
	}

}

void	fill_philos(t_philosophers *x)
{
	int	i;

	i = -1;
	x->philos = malloc (sizeof(t_philo) * x->n);
	while (++i < x->n)
	{
		x->philos[i] = malloc (sizeof(t_philo));
		x->philos[i]->n = i + 1;
		x->philos[i]->left_fork = 0;
		x->philos[i]->right_fork = 0;
		x->philos[i]->n_meals = 0;
	}
	i = -1;
	while (!x->dieded)
	{
		while (++i < x->n)
		{
			pthread_create(&x->philos[i]->thread, NULL, philo_loop, \
							(void *)x->philos[i]);
			usleep(100);
		}
	}
}

int	init_philosophers(char *argv[], t_philosophers *philo, int argc)
{
	int	i;

	i = -1;
	if (argc != 5 || argc != 6)
		exit(EXIT_FAILURE);
	philo->n = ft_atoi(argv[1]);
	philo->time_death = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	philo->n_eating = -1;
	philo->forks = malloc (sizeof(pthread_mutex_t) * philo->n);
	if (philo->n < 2 || philo->time_death < 0 || philo->time_eat < 0
		|| philo->time_sleep < 0)
		return (0);
	if (argc == 6)
	{
		philo->n_eating = ft_atoi(argv[5]);
		if (philo->n_eating <= 0)
			return (0);
	}
	return (philo);
}

int	main(int argc, char *argv[])
{
	t_philosophers	philo;
	int				safhc;

	init_philosophers(argv, &philo, argc);
	if (!safhc)
		return (0);


	exit(EXIT_FAILURE);
}
