/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:50:52 by maglagal          #+#    #+#             */
/*   Updated: 2024/05/02 13:32:54 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header_bonus.h"

void	thinking_state(t_philo *philo)
{
	sem_wait(philo->b_sema);
	check_death_variable(philo);
	printf("%zu %d is thinking\n", get_current_time() - philo->start_time,
		philo->id);
	check_death_variable(philo);
	sem_post(philo->b_sema);
}

void	sleeping_state(t_philo *philo)
{
	sem_wait(philo->b_sema);
	check_death_variable(philo);
	printf("%zu %d is sleeping\n", get_current_time() - philo->start_time,
		philo->id);
	check_death_variable(philo);
	sem_post(philo->b_sema);
	ft_sleep(philo->time_to_sleep);
}

void	eating_state(t_philo *philo)
{
	sem_wait(philo->sema);
	sem_wait(philo->b_sema);
	check_death_variable(philo);
	printf("%zu %d has taken a fork\n", get_current_time() - philo->start_time,
		philo->id);
	sem_post(philo->b_sema);
	sem_wait(philo->sema);
	sem_wait(philo->b_sema);
	check_death_variable(philo);
	printf("%zu %d has taken a fork\n", get_current_time() - philo->start_time,
		philo->id);
	printf("%zu %d is eating\n", get_current_time() - philo->start_time,
		philo->id);
	sem_post(philo->b_sema);
	sem_wait(philo->b_sema);
	check_death_variable(philo);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	sem_post(philo->b_sema);
	ft_sleep(philo->time_to_eat);
	sem_post(philo->sema);
	sem_post(philo->sema);
}

void	*philosophers_life_cycle(t_philo *philo)
{
	while (1)
	{
		eating_state(philo);
		sleeping_state(philo);
		thinking_state(philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo	philos[200];
	sem_t	*sema;
	sem_t	*b_sema;

	if (ac == 5 || ac == 6)
	{
		sema = NULL;
		b_sema = NULL;
		sem_unlink("/forks_semaphore");
		sem_unlink("/b_sema");
		if (create_semaphores(&sema, &b_sema, ft_atoi(av[1])))
			return (0);
		ft_parsing(ac, av);
		initialize_philos(av, philos);
		if (philos[0].num_times_to_eat == 0)
			return (0);
		initialize_semaphores_philos(philos, sema, b_sema);
		if (creating_philos(philos))
			return (0);
		terminate_processes(philos);
		terminate_semaphore(sema, b_sema);
	}
	else
		printf("Invalid arguments!!\n");
	return (0);
}
