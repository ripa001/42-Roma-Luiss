/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:29:22 by dripanuc          #+#    #+#             */
/*   Updated: 2022/04/02 02:44:12 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_thread(t_philosophers *x)
{
	int	i;

	i = 0;
	while (!x->dead)
	{
		while (x->philos[i] && !x->dead)
		{
			pthread_create(&x->philos[i]->thread, NULL, \
					philo_loop, (void *)x->philos[i]);
			usleep(100);
			i++;
		}
	}
}

void	*philo_loop(void *philo_void)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)philo_void;
	pthread_create(&thread, NULL, loop_check, philo);
	while (philo && !philo->data->dead)
	{
		my_eat(philo);
		print_mutex("is sleeping", philo);
		my_sleep(philo->data->time_sleep, philo->data);
		print_mutex("is thinking", philo);
	}
	return (NULL);
}

void	*loop_check(void *philo_void)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)philo_void;
	while (!philo->data->dead)
	{
		usleep(100);
		if ((get_time() - philo->data->time) - philo->lm >= \
				(unsigned long long)philo->data->td && !philo->eat)
		{
			philo_dead(philo);
			break ;
		}
		if (philo->data->n_e != -1 && philo->n_eating == philo->data->n_e)
		{
			philo->data->dead = 1;
			break ;
		}
	}
	if (philo->data->dead)
		exit(1);
	else
		exit(0);
	return (NULL);
}
