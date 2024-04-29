/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:32:20 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/27 17:25:19 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header_bonus.h"

void	safe_sem_close(sem_t *sema)
{
	if (sem_close(sema) != 0)
	{
		write(2, "sem_close() failed!!\n", 22);
		exit(3);
	}
}

void	check_philo_dead(t_philo *philo)
{
	int	i;

	i = 0;
	sem_wait(philo->b_sema);
	if (get_current_time() - philo->last_meal > philo->time_to_die)
	{
		philo->is_dead = 1;
		sem_post(philo->b_sema);
		safe_sem_close(philo->b_sema);
		sem_post(philo->sema);
		sem_post(philo->sema);
		safe_sem_close(philo->sema);
		exit(1);
	}
	sem_post(philo->b_sema);
}

void	check_total_eaten_meals(t_philo *philo)
{
	int	i;

	i = 0;
	sem_wait(philo->b_sema);
	if (philo->meals_eaten == philo->num_times_to_eat)
	{
		sem_post(philo->b_sema);
		safe_sem_close(philo->b_sema);
		sem_post(philo->sema);
		sem_post(philo->sema);
		safe_sem_close(philo->sema);
		exit(2);
	}
	sem_post(philo->b_sema);
}

void	check_death_variable(t_philo *philo)
{
	if (philo->is_dead)
		exit(1);
}
