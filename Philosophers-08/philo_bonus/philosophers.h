/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:44:07 by dripanuc          #+#    #+#             */
/*   Updated: 2022/04/02 02:33:20 by dripanuc         ###   ########.fr       */
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
	int					id;
	int					left_fork;
	int					right_fork;
	int					n_eating;
	int					lm;
	int					eat;
	pid_t				pid;
	pthread_t			thread;
}	t_philo;

typedef struct philosophers
{
	int				n;
	uint64_t		time;
	int				td;
	int				time_eat;
	int				n_e;
	int				n_finished;
	int				time_sleep;
	int				dead;
	t_philo			**philos;
	sem_t			*is_eating;
	sem_t			*forks;
	sem_t			*message;
}	t_philosophers;

uint64_t	get_time(void);
int			my_exit(int res, char *str);
void		philo_dead(t_philo *philo);
void		print_mutex(char *mess, t_philo	*philo);
void		my_sleep(long long time, t_philosophers *philo);
void		my_eat(t_philo *philo);
void		*loop_check(void *philo_void);
void		*philo_loop(void *philo_void);
void		fill_philos(t_philosophers *x);
void		p_thread(t_philosophers *x);
void		init(char *argv[], t_philosophers *philo);
void		end_success(t_philosophers *philo);
void		end(t_philosophers *philo);
long long	time_function(void);
int			init_philosophers(char *argv[], t_philosophers *philo, int argc);

#endif
