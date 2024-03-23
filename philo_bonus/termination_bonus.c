/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:52:30 by maglagal          #+#    #+#             */
/*   Updated: 2024/03/23 16:53:30 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header_bonus.h"

void	terminate_semaphore(sem_t *sema, sem_t *b_sema)
{
	safe_sem_close(sema);
	safe_sem_close(b_sema);
	sem_unlink("/forks_semaphore");
	sem_unlink("/b_sema");
}

void	kill_child_processes(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		kill(philos[i].p_pid, SIGKILL);
		i++;
	}
}

void	terminate_processes(t_philo *philos)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	status = 0;
	pid = waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) == 1)
	{
		while (philos[i].p_pid != pid)
			i++;
		printf("%zu %d died\n", get_current_time() - philos[i].start_time,
			philos[i].id);
		kill_child_processes(philos);
	}
	if (WEXITSTATUS(status) == 2)
	{
		while (i < philos[0].num_of_philos)
		{
			waitpid(philos[i].p_pid, &status, 0);
			i++;
		}
	}
}
