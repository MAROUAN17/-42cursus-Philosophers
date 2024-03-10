#include "philo_header.h"

void	check_philo_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (get_current_time() - philos[i].last_meal > philos[i].time_to_die && philos[i].last_meal != 0 && philos[i].eating == 0)
		{
			pthread_mutex_lock(philos[i].dead_lock);
			*(philos[i].dead) = 1;
			pthread_mutex_unlock(philos[i].dead_lock);
			pthread_mutex_lock(philos[i].write_lock);
			printf("%zu %d died\n", get_current_time(), philos[i].id);
			pthread_mutex_unlock(philos[i].write_lock);
			printf("last meal -> %zu\n", get_current_time() - philos[i].last_meal);
			printf("time to die -> %zu\n", philos[i].time_to_die);
			return ;
		}
		i++;
	}
}

int	check_total_eaten_meals(t_program *program)
{
	t_program 	*c_program;
	static int	i;
	static int	nbr_philos;

	c_program = (t_program *)program;
	if (i < c_program->philos[i].num_of_philos)
	{
		if (c_program->philos[i].meals_eaten == c_program->philos[i].num_times_to_eat)
			nbr_philos++;
		i++;
	}
	if (nbr_philos == c_program->philos[0].num_of_philos)
	{
        pthread_mutex_lock(c_program->philos[0].dead_lock);
        *(c_program->philos[0].dead) = 1;
        pthread_mutex_unlock(c_program->philos[0].dead_lock);
        pthread_mutex_lock(c_program->philos[0].write_lock);
		printf("all the philosophers have eaten the number of times they should eat!!\n");
        pthread_mutex_unlock(c_program->philos[0].write_lock);
		return (1);
	}
	if (i == c_program->philos[0].num_of_philos)
		i = 0;
	return (0);
}
