/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:18:59 by dripanuc          #+#    #+#             */
/*   Updated: 2022/04/02 02:20:07 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	end_success(t_philosophers *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n)
		free(philo->philos[i]);
	free(philo->philos);
	free(philo->forks);
	pthread_mutex_destroy(&philo->is_eating);
	pthread_mutex_destroy(&philo->death);
	pthread_mutex_destroy(&philo->message);
	exit(1);
}

void	p_thread(t_philosophers *x)
{
	int	i;

	i = 0;
	while (!x->dead)
	{
		while (x->philos[i] && !x->dead)
		{
			pthread_create(&x->philos[i]->thread, NULL, philo_loop, \
				(void *)x->philos[i]);
			usleep(100);
			i++;
		}
	}
}

void	my_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_mutex("has taken a fork", philo);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_mutex("has taken a fork", philo);
	print_mutex("is eating", philo);
	pthread_mutex_lock(&philo->data->is_eating);
	philo->eating = 1;
	if (++philo->n_eating == philo->data->target_eating)
		if (++philo->data->n_finished == philo->data->n)
			my_exit(1, "Tutti i filosofi hanno finito di mangiare");
	philo->last_meal = get_time() - philo->data->time;
	pthread_mutex_unlock(&philo->data->is_eating);
	my_sleep(philo->data->time_eat, philo->data);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	philo->eating = 0;
}

void	*philo_loop(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	if (philo->id % 2)
		usleep(15000);
	while (philo && !philo->data->dead)
	{
		my_eat(philo);
		print_mutex("is sleeping", philo);
		my_sleep(philo->data->time_sleep, philo->data);
		print_mutex("is thinking", philo);
	}
	return (NULL);
}
