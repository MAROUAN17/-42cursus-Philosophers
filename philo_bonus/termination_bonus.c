/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:52:30 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/29 11:03:04 by maglagal         ###   ########.fr       */
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

void	waiting_for_child_processes(t_philo *philos)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i < philos[0].num_of_philos - 1)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			kill_child_processes(philos, philos[0].num_of_philos);
			return ;
		}
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
	pid = safe_waitpid(-1, &status);
	if (pid == -1)
	{
		kill_child_processes(philos, philos[0].num_of_philos);
		return ;
	}
	if (WEXITSTATUS(status) == 1)
	{
		while (philos[i].p_pid != pid)
			i++;
		printf("%zu %d died\n", get_current_time() - philos[i].start_time,
			philos[i].id);
		kill_child_processes(philos, philos[0].num_of_philos);
	}
	if (WEXITSTATUS(status) == 2)
		waiting_for_child_processes(philos);
	if (WEXITSTATUS(status) == 3)
		kill_child_processes(philos, philos[0].num_of_philos);
}
