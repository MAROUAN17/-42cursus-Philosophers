/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:08:54 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/29 11:53:39 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	initialize_program(t_program *program, t_philo *philos)
{
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	creation_lock;

	if (pthread_mutex_init(&dead_lock, NULL))
		return (1);
	if (pthread_mutex_init(&meal_lock, NULL))
		return (1);
	if (pthread_mutex_init(&write_lock, NULL))
		return (1);
	if (pthread_mutex_init(&creation_lock, NULL))
		return (1);
	program->dead_flag = 0;
	program->philos = philos;
	program->dead_lock = dead_lock;
	program->meal_lock = meal_lock;
	program->write_lock = write_lock;
	program->creation_lock = creation_lock;
	return (0);
}

void	initialize_starttime(t_philo *philos, int nbr_philos)
{
	int		i;
	size_t	starttime;

	i = 0;
	starttime = get_current_time();
	while (i < nbr_philos)
	{
		philos[i].start_time = starttime;
		i++;
	}
}

int	create_thread_and_join(t_philo *philos, int nbr_philos)
{
	int		i;

	i = 0;
	while (i < nbr_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philosophers_life_cycle,
				&philos[i]) != 0)
		{
			write(2, "pthread_create() failed!!\n", 25);
			return (1);
		}
		i++;
	}
	initialize_starttime(philos, nbr_philos);
	pthread_mutex_unlock(philos[i - 1].creation_lock);
	i = 0;
	while (i < nbr_philos)
	{
		safe_thread_join(&philos[i], philos[i].thread);
		i++;
	}
	return (0);
}

void	initialize_philos(char **args, t_philo *philos,
	pthread_mutex_t *forks, t_program *program)
{
	int	i;

	i = 0;
	while (i < ft_atoi(args[1]))
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_current_time();
		philos[i].time_to_die = ft_atoi(args[2]);
		philos[i].time_to_eat = ft_atoi(args[3]);
		philos[i].time_to_sleep = ft_atoi(args[4]);
		philos[i].num_of_philos = ft_atoi(args[1]);
		if (args[5])
			philos[i].num_times_to_eat = ft_atoi(args[5]);
		else
			philos[i].num_times_to_eat = -1;
		philos[i].dead = &(program->dead_flag);
		philos[i].r_fork = &forks[i];
		philos[i].l_fork = &forks[(i + 1) % ft_atoi(args[1])];
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].creation_lock = &program->creation_lock;
		i++;
	}
}

int	initialize_forks(pthread_mutex_t *forks, int nbr_philos)
{
	int	i;

	i = 0;
	while (i < nbr_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			write(2, "pthread_mutex_init() failed!!\n", 31);
			return (1);
		}
		i++;
	}
	return (0);
}
