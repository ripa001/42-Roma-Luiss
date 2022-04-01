/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:48:14 by dripanuc          #+#    #+#             */
/*   Updated: 2022/03/31 19:39:10 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	end_success(t_philosophers *philo)
{
	int i;

	i = -1;
	while (++i < philo->n)
		free(philo->philos[i]);
	free(philo->philos);
	free(philo->forks);
	pthread_mutex_destroy(&philo->is_eating);
	pthread_mutex_destroy(&philo->death);
	pthread_mutex_destroy(&philo->message);
}

void	print_mutex(char *mess, t_philo	*philo)
{
	if (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->message);
		printf("[%llu] %d %s\n", get_time() - philo->data->time, philo->id, mess);
		pthread_mutex_unlock(&philo->data->message);
	}
}

long long	time_function(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void		my_sleep(long long time, t_philosophers *philo)
{
	long long i;

	i = time_function();
	while (!(philo->dead))
	{
		if (time_function() - i >= time)
			break ;
		usleep(50);
	}
}

void my_eat(t_philo *philo)
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

void	philo_dead(t_philosophers *philo, int i)
{
	pthread_mutex_lock(&philo->death);
	pthread_mutex_lock(&philo->message);
	printf("[%llu] %d died\n", get_time() - philo->time, philo->philos[i]->id);
	philo->dead = 1;
}

void	*loop_check(void *philo_void)
{
	t_philosophers	*philo;
	int		i;

	i = 0;
	philo = (t_philosophers *)philo_void;
	while (!philo->dead)
	{
		i = 0;
		while (philo->philos[i] && !philo->dead)
		{
			if (((get_time() - philo->time) - philo->philos[i]->last_meal >= philo->time_death) && !philo->philos[i]->eating)
				philo_dead(philo, i);
			i++;
			usleep(100);
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
		x-> philos[i]= malloc (sizeof(t_philo));
		x->philos[i]->id = i + 1;
		x->philos[i]->left_fork = i;
		x->philos[i]->right_fork = (i + 1) % x->n;
		x->philos[i]->n_eating = 0;
		x->philos[i]->eating = 0;
		x->philos[i]->data = x;
	}
	x->philos[i] = 0;
}

void p_thread(t_philosophers *x)
{
	int i;

	i = 0;
	while (!x->dead)
	{
		while (x->philos[i] && !x->dead)
		{
			pthread_create(&x->philos[i]->thread, NULL, philo_loop,	(void *)x->philos[i]);
			usleep(100);
			i++;
		}
	}
}

void init(char *argv[], t_philosophers *philo)
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
		my_exit(0, "Errore argomenti: Tutti i parametri devono essere positivi");
	if (philo->n < 2)
		my_exit(0, "Errore argomenti: Il numero di filosofi deve essere maggiore di 1");
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->n);
}

int	init_philosophers(char *argv[], t_philosophers *philo, int argc)
{
	int	i;
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

int	main(int argc, char *argv[])
{
	t_philosophers	philo;

	init_philosophers(argv, &philo, argc);
}
