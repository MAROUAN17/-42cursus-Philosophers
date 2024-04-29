/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:33:17 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/29 10:12:22 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header_bonus.h"

void	check_time_philo_eat(void *time_to_eat_char)
{
	int	time_to_eat;

	check_number(time_to_eat_char);
	time_to_eat = ft_atoi(time_to_eat_char);
	if (time_to_eat < 60)
	{
		printf("Non valid time to eat!!\n");
		exit(1);
	}
}

void	check_time_philo_sleep(void *time_to_sleep_char)
{
	int	time_to_sleep;

	check_number(time_to_sleep_char);
	time_to_sleep = ft_atoi(time_to_sleep_char);
	if (time_to_sleep < 60)
	{
		printf("Non valid time to sleep!!\n");
		exit(1);
	}
}

void	check_total_number_of_eating(char *total_eating_char)
{
	int	total_eating;

	check_number(total_eating_char);
	total_eating = ft_atoi(total_eating_char);
	if (total_eating < 0)
	{
		printf("Non valid number of total meals for each philosopher!!\n");
		exit(1);
	}
}
