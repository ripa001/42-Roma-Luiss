/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:44:07 by dripanuc          #+#    #+#             */
/*   Updated: 2022/04/02 03:20:36 by dripanuc         ###   ########.fr       */
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

typedef struct philo
{
	struct philosophers	*data;
	int					id;
	int					left_fork;
	int					right_fork;
	int					n_eating;
	int					last_meal;
	int					eating;
	pthread_t			thread;
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
	pthread_mutex_t	death;
	pthread_mutex_t	finish;
	pthread_mutex_t	is_eating;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
}	t_philosophers;

uint64_t	get_time(void);
int			my_exit(int res, char *str);
void		end_success(t_philosophers *philo);
void		print_mutex(char *mess, t_philo	*philo);
void		my_sleep(long long time, t_philosophers *philo);
void		my_eat(t_philo *philo);
void		*philo_loop(void *philo_void);
void		philo_dead(t_philosophers *philo, int i);
void		*loop_check(void *philo_void);
void		fill_philos(t_philosophers *x);
void		p_thread(t_philosophers *x);
long long	time_function(void);
int			init_philosophers(char *argv[], t_philosophers *philo, int argc);
int			ft_strisdigit(char *str);

#endif