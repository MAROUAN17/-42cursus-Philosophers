/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:52:30 by maglagal          #+#    #+#             */
/*   Updated: 2024/05/02 14:20:02 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header_bonus.h"

int	create_semaphores(sem_t **sema, sem_t **b_sema, int nbr_philos)
{
	*sema = safe_sem_open("/forks_semaphore", nbr_philos);
	if (!*sema)
		return (1);
	*b_sema = safe_sem_open("/b_sema", 1);
	if (!*b_sema)
	{
		safe_sem_close(*sema);
		safe_sem_unlink("/forks_semaphore");
		return (1);
	}
	return (0);
}

void	terminate_semaphore(sem_t *sema, sem_t *b_sema)
{
	safe_sem_close(sema);
	safe_sem_close(b_sema);
	safe_sem_unlink("/forks_semaphore");
	safe_sem_unlink("/b_sema");
}

void	kill_child_processes(t_philo *philos, int total_philos)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (i < total_philos)
	{
		if (kill(philos[i].p_pid, SIGKILL) > 0)
		{
			write(1, "kill() failed!!\n", 17);
			check = 1;
		}
		i++;
	}
	if (check)
	{
		terminate_semaphore(philos[0].sema, philos[0].b_sema);
		exit(1);
	}
}

void	terminate_processes(t_philo *philos)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	status = 0;
	pid = safe_waitpid(-1, &status);
	if (pid == -1)
	{
		kill_child_processes(philos, philos[0].num_of_philos);
		return ;
	}
	if (WEXITSTATUS(status) == 1)
		check_death_child_process(philos, pid);
	if (WEXITSTATUS(status) == 2)
		kill_child_processes(philos, philos[0].num_of_philos);
	if (WEXITSTATUS(status) == 3)
		kill_child_processes(philos, philos[0].num_of_philos);
}
