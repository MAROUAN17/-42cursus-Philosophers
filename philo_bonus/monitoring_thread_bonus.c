/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_thread_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:50:21 by maglagal          #+#    #+#             */
/*   Updated: 2024/03/23 15:25:53 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header_bonus.h"

void	creating_monitor_thread(t_philo *philo)
{
	pthread_t	thread_monitor;

	pthread_create(&thread_monitor, NULL, monitoring, philo);
	pthread_detach(thread_monitor);
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
