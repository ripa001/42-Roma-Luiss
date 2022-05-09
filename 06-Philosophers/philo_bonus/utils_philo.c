/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:46:05 by dripanuc          #+#    #+#             */
/*   Updated: 2022/04/02 02:28:27 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t	get_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * (uint64_t)1000) + (timeval.tv_usec / 1000));
}

void	philo_dead(t_philo *philo)
{
	sem_wait(philo->data->message);
	printf("[%llu] %d died\n", get_time() - philo->data->time, philo->id);
	philo->data->dead = 1;
}

int	my_exit(int res, char *str)
{
	printf("%s\n", str);
	exit(res);
	return (res);
}

void	print_mutex(char *mess, t_philo	*philo)
{
	if (!philo->data->dead)
	{
		sem_wait(philo->data->message);
		printf("[%llu] %d %s\n", \
			get_time() - philo->data->time, philo->id, mess);
		sem_post(philo->data->message);
	}
}

long long	time_function(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
