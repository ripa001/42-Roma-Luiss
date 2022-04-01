/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:46:05 by dripanuc          #+#    #+#             */
/*   Updated: 2022/03/27 19:19:47 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t	get_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * (uint64_t)1000) + (timeval.tv_usec / 1000));
}

void	philo_dead(t_philosophers *philo, int i)
{
	sem_wait(philo->message);
	printf("[%llu] %d died\n", get_time() - philo->time, philo->philos[i]->id);
	philo->dead = 1;
}

int my_exit(int res, char *str)
{
	printf("%s\n", str);
	exit(res);
	return (res);
}
