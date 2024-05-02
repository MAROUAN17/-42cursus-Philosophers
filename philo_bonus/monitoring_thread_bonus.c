/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_thread_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:50:21 by maglagal          #+#    #+#             */
/*   Updated: 2024/05/02 14:21:38 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header_bonus.h"

void	creating_monitor_thread(t_philo *philo)
{
	pthread_t	thread_monitor;

	if (pthread_create(&thread_monitor, NULL, monitoring, philo) != 0)
	{
		write(2, "pthread_create() failed!!\n", 27);
		exit(1);
	}
	if (pthread_detach(thread_monitor) != 0)
	{
		write(2, "pthread_detach() failed!!\n", 27);
		safe_sem_close(philo->sema);
		safe_sem_close(philo->b_sema);
		exit (1);
	}
}

void	*monitoring(void *philo)
{
	t_philo		*c_philo;

	c_philo = (t_philo *)philo;
	while (1)
	{
		if (c_philo->num_times_to_eat != -1)
			check_total_eaten_meals(c_philo);
		check_philo_dead(c_philo);
	}
	return (NULL);
}

void	check_death_child_process(t_philo *philos, pid_t pid)
{
	int	i;

	i = 0;
	while (philos[i].p_pid != pid)
		i++;
	printf("%zu %d died\n", get_current_time() - philos[i].start_time,
		philos[i].id);
	kill_child_processes(philos, philos[0].num_of_philos);
}
