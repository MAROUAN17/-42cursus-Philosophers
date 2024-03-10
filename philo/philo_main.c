#include "philo_header.h"

void	*monitor(void *program)
{
	t_program	*c_program;

	c_program = (t_program *)program;
	while (1)
	{
		if (c_program->philos->num_times_to_eat != -1)
			check_total_eaten_meals(c_program);
		check_philo_dead(c_program->philos);
		if (c_program->dead_flag == 1)
		{
			destroying_mutexes(c_program);
			detach_threads(c_program->philos);
			exit(1);
		}
	}
	return (NULL);
}

void	*sleeping_state(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%zu %d is sleeping\n", get_current_time(), philo->id);
	pthread_mutex_unlock(philo->write_lock);
	ft_sleep(philo->time_to_sleep);
	return (NULL);
}

void	*eating_state(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->meal_lock);
	pthread_mutex_lock(philo->write_lock);
	printf("%zu %d has taken a fork\n", get_current_time(), philo->id);
	printf("%zu %d is eating\n", get_current_time(), philo->id);
	pthread_mutex_unlock(philo->write_lock);
	philo->eating = 1;
	ft_sleep(philo->time_to_eat);
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->eating = 0;
	return (NULL);
}

void	*philosophers_life_cycle(void *philo)
{
	t_philo *actual_philo;

	actual_philo = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(actual_philo->write_lock);
		printf("%zu %d is thinking\n", get_current_time(), actual_philo->id);
		pthread_mutex_unlock(actual_philo->write_lock);
		eating_state(actual_philo);
		sleeping_state(actual_philo);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	t_program		program;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	int             nbr_philos;
	int             i;
	int             nbr_times_to_eat;

	if (ac == 5 || ac == 6)
	{
		i = 0;
		ft_parsing(ac, av);
		nbr_philos = ft_atoi(av[1]);
		if (ac == 6)
			nbr_times_to_eat = ft_atoi(av[5]);
		else
			nbr_times_to_eat = -1;
		initialize_program(&program, philos);
		initialize_forks(forks, nbr_philos);
		initialize_philos(av, philos, forks, &program);
	}
	else
	{
		printf("Invalid arguments!!\n"); 
		exit(1);
	}
	return (0);
}