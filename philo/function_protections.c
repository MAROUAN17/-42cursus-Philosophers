/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_protections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:16:40 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/27 18:17:09 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	safe_thread_join(t_philo *philo, pthread_t thread)
{
	if (pthread_join(thread, NULL) != 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		write(2, "pthread_join() failed!!\n", 25);
		return ;
	}
}

int	safe_mutex_destroy(t_philo *philo, pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex) != 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		write(2, "pthread_mutex_destroy() failed!!\n", 34);
		return (1);
	}
	return (0);
}
