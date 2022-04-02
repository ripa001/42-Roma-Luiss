/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:48:14 by dripanuc          #+#    #+#             */
/*   Updated: 2022/04/02 02:52:53 by dripanuc         ###   ########.fr       */
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

void	*loop_check(void *philo_void)
{
	t_philosophers	*philo;
	int				i;

	i = 0;
	philo = (t_philosophers *)philo_void;
	while (!philo->dead)
	{
		i = 0;
		while (philo->philos[i] && !philo->dead)
		{
			if (((get_time() - philo->time) - philo->philos[i]->last_meal >= \
					(unsigned long long)philo->time_death) \
						&& !philo->philos[i]->eating)
				philo_dead(philo, i);
			i++;
			usleep(50);
		}
	}
	return (NULL);
}

void	fill_philos(t_philosophers *x)
{
	int	i;

	i = -1;
	x->philos = malloc (sizeof(t_philo) * x->n + 1);
	x->dead = 0;
	while (++i < x->n)
	{
		x->philos[i] = malloc (sizeof(t_philo));
		x->philos[i]->id = i + 1;
		x->philos[i]->left_fork = i;
		x->philos[i]->right_fork = (i + 1) % x->n;
		x->philos[i]->n_eating = 0;
		x->philos[i]->eating = 0;
		x->philos[i]->data = x;
	}
	x->philos[i] = 0;
}

void	init(char *argv[], t_philosophers *philo)
{
	philo->n = ft_atoi(argv[1]);
	philo->time_death = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	philo->target_eating = -1;
	philo->n_finished = 0;
	philo->time = get_time();
	pthread_mutex_init(&philo->death, NULL);
	pthread_mutex_init(&philo->finish, NULL);
	pthread_mutex_init(&philo->is_eating, NULL);
	pthread_mutex_init(&philo->message, NULL);
	if (philo->time_death < 0 || philo->time_eat < 0
		|| philo->time_sleep < 0)
		my_exit(0, "Errore argomenti: Tutti i parametri \
			devono essere positivi");
	if (philo->n < 1)
		my_exit(0, "Errore argomenti: Il numero di filosofi \
			deve essere maggiore di 0");
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->n);
}

int	init_philosophers(char *argv[], t_philosophers *philo, int argc)
{
	int			i;
	pthread_t	thread;

	i = -1;
	if (argc < 5 || argc > 6)
		my_exit(0, "Errore argomenti: Sono accettati 4 o 5 argomenti");
	init(argv, philo);
	while (++i < philo->n)
		pthread_mutex_init(&philo->forks[i], NULL);
	pthread_create(&thread, NULL, loop_check, philo);
	fill_philos(philo);
	if (argc == 6)
	{
		philo->target_eating = ft_atoi(argv[5]);
		if (philo->target_eating <= 0)
			my_exit(0, "Errore argomenti: Minimo numero di pasti 1");
	}
	p_thread(philo);
	return (1);
}
