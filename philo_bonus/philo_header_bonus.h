/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:36:19 by maglagal          #+#    #+#             */
/*   Updated: 2024/04/28 11:54:25 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_BONUS_H
# define PHILO_HEADER_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_philo
{
	pid_t			p_pid;
	int				id;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	int				num_times_to_eat;
	int				meals_eaten;
	int				num_of_philos;
	size_t			start_time;
	size_t			last_meal;
	sem_t			*b_sema;
	sem_t			*sema;
	sem_t			*d_sema;
	int				philos_eaten_total_meals;
	int				total_philos;
	int				is_dead;
}					t_philo;

int		ft_atoi(const char *str);
void	ft_parsing(int number_args, char **args);
int		creating_philos(t_philo *philos);
void	initialize_philos(char **args, t_philo *philos);
void	initialize_semaphores_philos(t_philo *philos,
			sem_t *sema, sem_t *b_sema);
void	terminate_semaphore(sem_t *sema, sem_t *b_sema);
void	*philosophers_life_cycle(t_philo *philo);
size_t	get_current_time(void);
size_t	ft_sleep(size_t milliseconds);
void	check_philo_dead(t_philo *philo);
void	check_total_eaten_meals(t_philo *philo);
void	creating_monitor_thread(t_philo *philo);
void	*monitoring(void *program);
void	terminate_processes(t_philo *philos);
void	check_number(char *arg);
void	check_time_philo_eat(void *time_to_eat_char);
void	check_time_philo_sleep(void *time_to_sleep_char);
void	check_total_number_of_eating(char *total_eating_char);
void	check_death_variable(t_philo *philo);
void	kill_child_processes(t_philo *philos, int total_philos);
void	safe_sem_close(sem_t *sema);
int		safe_sem_unlink(char *sema_name);
sem_t	*safe_sem_open(char *sema_name, int ini_value);
int		safe_waitpid(pid_t pid, int *r_status);
int		handle_fork_fail(t_philo *philos, int nbr);
int		create_semaphores(sem_t **sema, sem_t **b_sema, int nbr_philos);

#endif
