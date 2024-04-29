/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:15:04 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/25 14:50:23 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	check_number(char *arg)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (*(arg + i))
	{
		if (*(arg + i) < '0' || *(arg + i) > '9')
		{
			printf("Non valid argument!!\n");
			check = 1;
			return (check);
		}
		i++;
	}
	return (check);
}

int	check_number_of_philos(char *number_philos_char)
{
	int	number_philos;
	int	check;

	check = 0;
	if (check_number(number_philos_char))
	{
		check = 1;
		return (check);
	}
	number_philos = ft_atoi(number_philos_char);
	if (number_philos > 200 || number_philos <= 0)
	{
		printf("Non valid number of philos!!\n");
		check = 1;
		return (check);
	}
	return (check);
}

int	check_time_philo_die(void *time_to_die_char)
{
	int	time_to_die;
	int	check;

	check = 0;
	if (check_number(time_to_die_char))
	{
		check = 1;
		return (check);
	}
	time_to_die = ft_atoi(time_to_die_char);
	if (time_to_die < 60)
	{
		printf("Non valid time to die!!\n");
		check = 1;
		return (check);
	}
	return (check);
}

int	check_time_philo_eat(void *time_to_eat_char)
{
	int	time_to_eat;
	int	check;

	check = 0;
	if (check_number(time_to_eat_char))
	{
		check = 1;
		return (check);
	}
	time_to_eat = ft_atoi(time_to_eat_char);
	if (time_to_eat < 60)
	{
		printf("Non valid time to eat!!\n");
		check = 1;
		return (check);
	}
	return (check);
}

int	ft_parsing(int number_args, char **args)
{
	int	check;

	check = 0;
	check = check_number_of_philos(args[1]);
	if (check)
		return (check);
	check = check_time_philo_die(args[2]);
	if (check)
		return (check);
	check = check_time_philo_eat(args[3]);
	if (check)
		return (check);
	check = check_time_philo_sleep(args[4]);
	if (check)
		return (check);
	if (number_args == 6)
	{
		check = check_total_number_of_eating(args[5]);
		if (check)
			return (check);
	}
	return (check);
}
