/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:29:41 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/27 18:23:57 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	destroying_mutexes(t_program *program)
{
	int	i;
	int	total_philos;

	i = 0;
	total_philos = program->philos[0].num_of_philos;
	while (i < total_philos)
	{
		if (safe_mutex_destroy(&program->philos[0],
				program->philos[i].r_fork))
			return ;
		i++;
	}
	if (safe_mutex_destroy(&program->philos[0],
			program->philos[0].meal_lock))
		return ;
	if (safe_mutex_destroy(&program->philos[0],
			program->philos[0].dead_lock))
		return ;
	if (safe_mutex_destroy(&program->philos[0],
			program->philos[0].write_lock))
		return ;
}
