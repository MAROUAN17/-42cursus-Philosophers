/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:30:28 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/24 10:43:26 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header_bonus.h"

size_t	ft_sleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < milliseconds)
		usleep(100);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		write(2, "Error getting current time\n", 30);
		exit(1);
	}
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}
