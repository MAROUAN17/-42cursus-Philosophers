#include "philo_header.h"


void    initialize_program(t_program *program, t_philo *philos)
{
    pthread_mutex_t p_dead_lock;
    pthread_mutex_t p_meal_lock;
    pthread_mutex_t p_write_lock;

    pthread_mutex_init(&p_dead_lock, NULL);
    pthread_mutex_init(&p_meal_lock, NULL);
    pthread_mutex_init(&p_write_lock, NULL);
    program->dead_flag = 0;
    program->philos = philos;
    program->dead_lock = p_dead_lock;
    program->meal_lock = p_meal_lock;
    program->write_lock = p_write_lock;
}

void    creating_monitoring_thread(t_program *program)
{
	pthread_t   monitor_thread;

	pthread_create(&monitor_thread, NULL, monitor, program);
}

void    create_thread_and_join(t_philo *philos, int nbr_philos)
{
	int i;

	i = 0;
	while (i < nbr_philos)
	{
        pthread_create(&philos[i].thread, NULL, philosophers_life_cycle, &philos[i]);
		i++;
	}
    i = 0;
    while (i < nbr_philos)
    {
		pthread_join(philos[i].thread, NULL);
        i++;
    }
}

void    initialize_philos(char **args, t_philo *philos, pthread_mutex_t *forks,
    t_program *program)
{
    int             i;
    int             nbr_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    pthread_mutex_t write_lock;
    pthread_mutex_t dead_lock;
    pthread_mutex_t meal_lock;

    pthread_mutex_init(&write_lock, NULL);
    pthread_mutex_init(&dead_lock, NULL);
    pthread_mutex_init(&meal_lock, NULL);
    i = 0;
    nbr_philos = ft_atoi(args[1]);
    time_to_die = ft_atoi(args[2]);
    time_to_eat = ft_atoi(args[3]);
    time_to_sleep = ft_atoi(args[4]);
    while (i < nbr_philos)
    {
        philos[i].id = i + 1;
        philos[i].eating = 0;
        philos[i].meals_eaten = 0;
        philos[i].last_meal = 0;
        philos[i].time_to_die = time_to_die;
        philos[i].time_to_eat = time_to_eat;
        philos[i].time_to_sleep = time_to_sleep;
        philos[i].start_time = 0;
        philos[i].num_of_philos = nbr_philos;
        if (args[5])
            philos[i].num_times_to_eat = ft_atoi(args[5]);
        else
            philos[i].num_times_to_eat = -1;
        philos[i].dead = &program->dead_flag;
        philos[i].r_fork = &forks[i];
        philos[i].l_fork = &forks[(i + 1) % nbr_philos];
        philos[i].write_lock = &write_lock;
        philos[i].dead_lock = &dead_lock;
        philos[i].meal_lock = &meal_lock;
        i++;
    }
    creating_monitoring_thread(program);
    create_thread_and_join(philos, nbr_philos);
}

void    initialize_forks(pthread_mutex_t *forks, int nbr_philos)
{
    int i;

    i = 0;
    while (i < nbr_philos)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}
