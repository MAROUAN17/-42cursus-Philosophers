/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_protections_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:24:28 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/28 10:59:19 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header_bonus.h"

int	safe_sem_unlink(char *sema_name)
{
	if (sem_unlink(sema_name) != 0)
	{
		write(2, "sem_unlink() failed!!\n", 23);
		return (1);
	}
	return (0);
}

sem_t	*safe_sem_open(char *sema_name, int ini_value)
{
	sem_t	*ptr_sem;

	ptr_sem = sem_open(sema_name, O_CREAT, 0644, ini_value);
	if (ptr_sem == SEM_FAILED)
	{
		write(2, "sem_open() failed!!\n", 21);
		return (NULL);
	}
	return (ptr_sem);
}

int	safe_waitpid(pid_t pid, int *r_status)
{
	int	result;

	result = waitpid(pid, r_status, 0);
	if (result == -1)
		write(2, "waitpid() failed!!\n", 20);
	return (result);
}

int	handle_fork_fail(t_philo *philos, int nbr)
{
	write(2, "fork() failed!!\n", 17);
	kill_child_processes(philos, nbr);
	terminate_semaphore(philos[0].sema, philos[0].b_sema);
	return (1);
}
