/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:00:00 by maglagal          #+#    #+#             */
/*   Updated: 2024/03/23 14:40:00 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	sleeping_state(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead) == 1)
	{
		unlocking_all_mutexes(philo);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
	printf("%zu %d is sleeping\n", get_current_time() - philo->start_time,
		philo->id);
	pthread_mutex_unlock(philo->write_lock);
	ft_sleep(philo->time_to_sleep);
}

void	thinking_state(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead) == 1)
	{
		unlocking_all_mutexes(philo);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
	printf("%zu %d is thinking\n", get_current_time() - philo->start_time,
		philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

void	eating_state(t_philo *philo)
{
	locking_forks(philo);
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead) == 1)
	{
		unlocking_all_mutexes(philo);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
	printf("%zu %d is eating\n", get_current_time() - philo->start_time,
		philo->id);
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_sleep(philo->time_to_eat);
	unlocking_forks(philo);
}

void	*philosophers_life_cycle(void *philo)
{
	t_philo	*actual_philo;

	actual_philo = (t_philo *)philo;
	if (actual_philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		eating_state(actual_philo);
		sleeping_state(actual_philo);
		thinking_state(actual_philo);
		pthread_mutex_lock(actual_philo->dead_lock);
		if (*(actual_philo->dead) == 1)
		{
			unlocking_all_mutexes(philo);
			return (NULL);
		}
		pthread_mutex_unlock(actual_philo->dead_lock);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_program		program;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	int				nbr_philos;
	int				nbr_times_to_eat;

	if (ac == 5 || ac == 6)
	{
		if (ft_parsing(ac, av))
			return (0);
		nbr_philos = ft_atoi(av[1]);
		if (ac == 6)
			nbr_times_to_eat = ft_atoi(av[5]);
		else
			nbr_times_to_eat = -1;
		initialize_program(&program, philos);
		initialize_forks(forks, nbr_philos);
		initialize_philos(av, philos, forks, &program);
		creating_monitoring_thread(&program);
		create_thread_and_join(philos, nbr_philos);
		destroying_mutexes(&program);
	}
	else
		printf("Invalid arguments!!\n");
	return (0);
}
