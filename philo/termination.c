#include "philo_header.h"

void    destroying_mutexes(t_program *program)
{
    int i;

    i = 0;
    while (i < program->philos[i].num_of_philos)
    {
        pthread_mutex_destroy(program->philos[i].r_fork);
        i++;
    }
    pthread_mutex_destroy(program->philos[0].write_lock);
    pthread_mutex_destroy(program->philos[0].meal_lock);
    pthread_mutex_destroy(program->philos[0].dead_lock);
}

void    detach_threads(t_philo *philos)
{
    int i;
    int total_philos;

    i = 0;
    total_philos = philos[0].num_of_philos;
    while (i < total_philos)
    {
        pthread_detach(philos[i].thread);
        i++;
    }
}