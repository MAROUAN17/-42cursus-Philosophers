#include "philo_header.h"

void    check_number(char *arg)
{
    int i;

    i = 0;
    while (*(arg + i))
    {
        if (*(arg + i) < '0' || *(arg + i) > '9')
        {
            printf("Non valid argument!!\n");
            exit(1);
        }
        i++;
    }
}

void    check_number_of_philos(char *number_philos_char)
{
    int number_philos;

    check_number(number_philos_char);
    number_philos = ft_atoi(number_philos_char);
    if (number_philos > 200 || number_philos <= 0)
    {
        printf("Non valid number of philos!!\n");
        exit(1);
    }
}

void    check_time_philo_die(void *time_to_die_char)
{
    int time_to_die;

    check_number(time_to_die_char);
    time_to_die = ft_atoi(time_to_die_char);
    if (time_to_die < 60)
    {
        printf("Non valid time to die!!\n");
        exit(1);
    }
}

void    check_time_philo_eat(void *time_to_eat_char)
{
    int time_to_eat;

    check_number(time_to_eat_char);
    time_to_eat = ft_atoi(time_to_eat_char);
    if (time_to_eat < 60)
    {
        printf("Non valid time to eat!!\n");
        exit(1);
    }
}

void    check_time_philo_sleep(void *time_to_sleep_char)
{
    int time_to_sleep;

    check_number(time_to_sleep_char);
    time_to_sleep = ft_atoi(time_to_sleep_char);
    if (time_to_sleep < 60)
    {
        printf("Non valid time to sleep!!\n");
        exit(1);
    }
}

void    check_number_of_meals(char *number_of_meals_char)
{
    int number_of_meals;

    check_number(number_of_meals_char);
    number_of_meals = ft_atoi(number_of_meals_char);
    if (number_of_meals < 0)
    {
        printf("Non valid number of meals!!\n");
        exit(1);
    }
}

void    check_total_number_of_eating(char *total_eating_char)
{
    int total_eating;

    check_number(total_eating_char);
    total_eating = ft_atoi(total_eating_char);
    if (total_eating < 0)
    {
        printf("Non valid number of total meals for each philosopher!!\n");
        exit(1);
    }

}

void ft_parsing(int number_args, char **args)
{
    check_number_of_philos(args[1]);
    check_time_philo_die(args[2]);
    check_time_philo_eat(args[3]);
    check_time_philo_sleep(args[4]);
    if (number_args == 6)
        check_total_number_of_eating(args[5]);
}