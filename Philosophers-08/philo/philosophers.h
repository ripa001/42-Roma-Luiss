/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:44:07 by dripanuc          #+#    #+#             */
/*   Updated: 2022/03/27 20:10:28 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include "libft/libft.h"

uint64_t	get_time(void);
typedef struct philo
{
	struct philosophers	*data;
	int				id;
	int				left_fork;
	int				right_fork;
	int				n_eating;
	int				last_meal;
	int				eating;
	pthread_t		thread;
}	t_philo;

typedef struct philosophers
{
	int				n;
	uint64_t		time;
	int				time_death;
	int				time_eat;
	int				target_eating;
	int				n_eating;
	int				time_sleep;
	int				dieded;
	t_philo			**philos;
	pthread_mutex_t	death;
	pthread_mutex_t	finish;
	pthread_mutex_t	is_eating;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
}	t_philosophers;

#endif
