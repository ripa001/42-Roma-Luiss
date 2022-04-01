/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:44:07 by dripanuc          #+#    #+#             */
/*   Updated: 2022/03/28 18:36:56 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include "libft/libft.h"


typedef struct philo
{
	struct philosophers	*data;
	int				id;
	int				left_fork;
	int				right_fork;
	int				n_eating;
	int				last_meal;
	int				eating;
	pid_t			pid;
	pthread_t		thread;
}	t_philo;

typedef struct philosophers
{
	int				n;
	uint64_t		time;
	int				time_death;
	int				time_eat;
	int				target_eating;
	int				n_finished;
	int				time_sleep;
	int				dead;
	t_philo			**philos;
	sem_t *is_eating;
	sem_t *forks;
	sem_t *message;
}	t_philosophers;

uint64_t	get_time(void);
int my_exit(int res, char *str);
void	philo_dead(t_philosophers *philo, int i);

#endif
