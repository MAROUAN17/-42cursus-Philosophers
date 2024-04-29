/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:28:47 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/27 18:05:22 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_H
# define PHILO_HEADER_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*creation_lock;
	pthread_mutex_t	*dead_var;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	creation_lock;
	pthread_mutex_t	dead_var;
	t_philo			*philos;
}					t_program;

int		ft_atoi(const char *str);
int		ft_parsing(int number_args, char **args);
int		initialize_program(t_program *program, t_philo *philos);
void	initialize_philos(char **args, t_philo *philos,
			pthread_mutex_t *forks, t_program *program);
int		initialize_forks(pthread_mutex_t *forks, int nbr_philos);
void	*philosophers_life_cycle(void *actual_philo);
size_t	ft_sleep(size_t milliseconds);
size_t	get_current_time(void);
void	*monitor(void *program);
void	destroying_mutexes(t_program *program);
void	check_philo_dead(t_philo *philos);
void	check_total_eaten_meals(t_program *program);
int		create_thread_and_join(t_philo *philos, int nbr_philos);
int		creating_monitoring_thread(t_program *program);
void	printing_fork_message(t_philo *philo);
void	locking_right_fork(t_philo *philo);
void	locking_left_fork(t_philo *philo);
void	unlocking_forks(t_philo *philo);
void	unlocking_all_mutexes(t_philo *philo);
void	locking_forks(t_philo *philo);
int		check_time_philo_sleep(void *time_to_sleep_char);
int		check_number_of_meals(char *number_of_meals_char);
int		check_total_number_of_eating(char *total_eating_char);
int		check_number(char *arg);
void	safe_thread_join(t_philo *philo, pthread_t thread);
int		safe_mutex_destroy(t_philo *philo, pthread_mutex_t *mutex);

#endif
