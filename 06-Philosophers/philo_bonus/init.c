/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:31:07 by dripanuc          #+#    #+#             */
/*   Updated: 2022/04/02 03:15:55 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		x->philos[i]->eat = 0;
		x->philos[i]->data = x;
		x->philos[i]->lm = 0;
	}
	x->philos[i] = 0;
}

void	init(char *argv[], t_philosophers *philo)
{
	philo->n = ft_atoi(argv[1]);
	philo->td = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	philo->n_e = -1;
	philo->n_finished = 0;
	philo->time = get_time();
	if (philo->td < 0 || philo->time_eat < 0
		|| philo->time_sleep < 0)
		my_exit(0, \
		"Errore argomenti: Tutti i parametri devono essere positivi");
	if (philo->n < 1)
		my_exit(0, \
		"Errore argomenti: Il numero di filosofi deve essere maggiore di 0");
	sem_unlink("sem_forks");
	sem_unlink("sem_message");
	sem_unlink("sem_eating");
	philo->forks = sem_open("sem_forks", O_CREAT, 0644, philo->n);
	philo->message = sem_open("sem_message", O_CREAT, 0644, 1);
	philo->is_eating = sem_open("sem_eating", O_CREAT, 0644, 1);
}

int	init_philosophers(char *argv[], t_philosophers *philo, int argc)
{
	int	i;

	i = -1;
	if (argc < 5 || argc > 6)
		my_exit(0, "Errore argomenti: Sono accettati 4 o 5 argomenti");
	init(argv, philo);
	fill_philos(philo);
	if (argc == 6)
	{
		philo->n_e = ft_atoi(argv[5]);
		if (philo->n_e <= 0)
			my_exit(0, "Errore argomenti: Minimo numero di pasti 1");
	}
	return (1);
}

int	ft_strisdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}
