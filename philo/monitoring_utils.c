/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:10:49 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/27 15:13:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	check_philo_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (get_current_time() - philos[i].last_meal > philos[i].time_to_die)
		{
			pthread_mutex_unlock(philos[i].meal_lock);
			pthread_mutex_lock(philos[i].dead_lock);
			*philos[i].dead = 1;
			pthread_mutex_unlock(philos[i].dead_lock);
			pthread_mutex_lock(philos[i].write_lock);
			printf("%zu %d died\n", get_current_time() - philos[i].last_meal,
				philos[i].id);
			pthread_mutex_unlock(philos[i].write_lock);
			if (philos[i].num_of_philos == 1)
				pthread_mutex_unlock(philos[i].r_fork);
			return ;
		}
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
}

void	check_total_eaten_meals(t_program *program)
{
	t_program	*c_program;
	int			i;
	int			nbr_philos;

	i = 0;
	nbr_philos = 0;
	c_program = (t_program *)program;
	while (i < c_program->philos[0].num_of_philos)
	{
		pthread_mutex_lock(c_program->philos[0].meal_lock);
		if (c_program->philos[i].meals_eaten
			>= c_program->philos[i].num_times_to_eat)
			nbr_philos++;
		pthread_mutex_unlock(c_program->philos[0].meal_lock);
		i++;
	}
	if (nbr_philos == c_program->philos[0].num_of_philos)
	{
		pthread_mutex_lock(c_program->philos[0].dead_lock);
		*(c_program->philos[0].dead) = 1;
		pthread_mutex_unlock(c_program->philos[0].dead_lock);
	}
}
