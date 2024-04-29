/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:15:15 by maglagal          #+#    #+#             */
/*   Updated: 2024/03/23 11:16:08 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	check_time_philo_sleep(void *time_to_sleep_char)
{
	int	time_to_sleep;
	int	check;

	check = 0;
	if (check_number(time_to_sleep_char))
	{
		check = 1;
		return (check);
	}
	time_to_sleep = ft_atoi(time_to_sleep_char);
	if (time_to_sleep < 60)
	{
		printf("Non valid time to sleep!!\n");
		check = 1;
		return (check);
	}
	return (check);
}

int	check_number_of_meals(char *number_of_meals_char)
{
	int	number_of_meals;
	int	check;

	check = 0;
	if (check_number(number_of_meals_char))
	{
		check = 1;
		return (check);
	}
	number_of_meals = ft_atoi(number_of_meals_char);
	if (number_of_meals < 0)
	{
		printf("Non valid number of meals!!\n");
		check = 1;
		return (check);
	}
	return (check);
}

int	check_total_number_of_eating(char *total_eating_char)
{
	int	total_eating;
	int	check;

	check = 0;
	if (check_number(total_eating_char))
	{
		check = 1;
		return (check);
	}
	total_eating = ft_atoi(total_eating_char);
	if (total_eating < 0)
	{
		printf("Non valid number of total meals for each philosopher!!\n");
		check = 1;
	}
	return (check);
}
