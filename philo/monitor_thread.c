/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:09:53 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/27 15:29:49 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	creating_monitoring_thread(t_program *program)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor, program) != 0)
	{
		write(2, "pthread_create() failed!!\n", 27);
		return (1);
	}
	if (pthread_detach(monitor_thread) != 0)
	{
		write(2, "pthread_detach() failed!!\n", 27);
		return (1);
	}
	return (0);
}

void	*monitor(void *program)
{
	t_program	*c_program;

	c_program = (t_program *)program;
	pthread_mutex_lock(&c_program->creation_lock);
	pthread_mutex_unlock(&c_program->creation_lock);
	while (1)
	{
		if (c_program->philos->num_times_to_eat != -1)
			check_total_eaten_meals(c_program);
		check_philo_dead(c_program->philos);
		pthread_mutex_lock(c_program->philos[0].dead_lock);
		if (c_program->dead_flag)
		{
			pthread_mutex_unlock(c_program->philos[0].dead_lock);
			return (NULL);
		}
		pthread_mutex_unlock(c_program->philos[0].dead_lock);
	}
	return (NULL);
}

void	unlocking_all_mutexes(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->dead_lock);
}
