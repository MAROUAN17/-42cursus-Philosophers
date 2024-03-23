/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:09:53 by maglagal          #+#    #+#             */
/*   Updated: 2024/03/23 15:45:46 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	creating_monitoring_thread(t_program *program)
{
	pthread_t	monitor_thread;

	pthread_create(&monitor_thread, NULL, monitor, program);
	pthread_detach(monitor_thread);
}

void	*monitor(void *program)
{
	int			check;
	t_program	*c_program;

	check = 0;
	c_program = (t_program *)program;
	while (1)
	{
		if (c_program->philos->num_times_to_eat != -1)
			check = check_total_eaten_meals(c_program);
		if (check == 1)
			return (NULL);
		check_philo_dead(c_program->philos);
		if (c_program->dead_flag)
			return (NULL);
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
