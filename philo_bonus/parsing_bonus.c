/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:32:52 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/29 09:55:39 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header_bonus.h"

void	check_number(char *arg)
{
	int	i;

	i = 0;
	if (!*(arg + i))
	{
		printf("Non valid argument!!\n");
		exit(1);
	}
	while (*(arg + i))
	{
		if (*(arg + i) < '0' || *(arg + i) > '9')
		{
			printf("Non valid argument!!\n");
			exit(1);
		}
		i++;
	}
}

void	check_number_of_philos(char *number_philos_char)
{
	int	number_philos;

	check_number(number_philos_char);
	number_philos = ft_atoi(number_philos_char);
	if (number_philos > 200 || number_philos <= 0)
	{
		printf("Non valid number of philos!!\n");
		exit(1);
	}
}

void	check_time_philo_die(void *time_to_die_char)
{
	int	time_to_die;

	check_number(time_to_die_char);
	time_to_die = ft_atoi(time_to_die_char);
	if (time_to_die < 60)
	{
		printf("Non valid time to die!!\n");
		exit(1);
	}
}

void	ft_parsing(int number_args, char **args)
{
	check_number_of_philos(args[1]);
	check_time_philo_die(args[2]);
	check_time_philo_eat(args[3]);
	check_time_philo_sleep(args[4]);
	if (number_args == 6)
		check_total_number_of_eating(args[5]);
}
