/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:03:42 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/27 15:16:44 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	locking_forks(t_philo *philo)
{
	if (philo->id == philo->num_of_philos)
	{
		locking_left_fork(philo);
		locking_right_fork(philo);
	}
	else
	{
		locking_right_fork(philo);
		locking_left_fork(philo);
	}
}

void	locking_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead) == 1)
	{
		unlocking_all_mutexes(philo);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
	printing_fork_message(philo);
}

void	locking_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead) == 1)
	{
		unlocking_all_mutexes(philo);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
	printing_fork_message(philo);
}

void	printing_fork_message(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead) == 1)
	{
		unlocking_all_mutexes(philo);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
	printf("%zu %d has taken a fork\n", get_current_time() - philo->start_time,
		philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

void	unlocking_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead))
	{
		unlocking_all_mutexes(philo);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
	if (philo->id == philo->num_of_philos)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}
