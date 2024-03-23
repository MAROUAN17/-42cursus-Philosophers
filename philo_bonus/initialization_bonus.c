/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:32:03 by maglagal          #+#    #+#             */
/*   Updated: 2024/03/23 12:38:29 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header_bonus.h"

void	initialize_philos(char **args, t_philo *philos,
	sem_t *sema, sem_t *b_sema)
{
	int		i;
	int		total_philos;

	i = 0;
	total_philos = ft_atoi(args[1]);
	while (i < total_philos)
	{
		philos[i].id = 0;
		philos[i].p_pid = 0;
		philos[i].num_of_philos = total_philos;
		philos[i].time_to_die = ft_atoi(args[2]);
		philos[i].time_to_eat = ft_atoi(args[3]);
		philos[i].time_to_sleep = ft_atoi(args[4]);
		philos[i].start_time = 0;
		philos[i].last_meal = get_current_time();
		philos[i].meals_eaten = 0;
		if (args[5])
			philos[i].num_times_to_eat = ft_atoi(args[5]);
		else
			philos[i].num_times_to_eat = -1;
		philos[i].sema = sema;
		philos[i].b_sema = b_sema;
		philos[i].is_dead = 0;
		i++;
	}
}

void	creating_philos(t_philo *philos)
{
	int		status;
	int		i;
	size_t	starttime;

	i = 0;
	status = 0;
	starttime = get_current_time();
	while (i < philos[0].num_of_philos)
	{
		philos[i].p_pid = fork();
		philos[i].id = i + 1;
		philos[i].start_time = starttime;
		if (philos[i].p_pid == 0)
		{
			creating_monitor_thread(&philos[i]);
			philosophers_life_cycle(&philos[i]);
		}
		i++;
	}
}
