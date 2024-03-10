#include "philo_header.h"

size_t  ft_sleep(size_t milliseconds)
{
    size_t  start;

    start = get_current_time();
    while (get_current_time() - start < milliseconds)
        usleep(50);
    return (0);
}

size_t get_current_time(void)
{
    struct timeval current_time;

    if (gettimeofday(&current_time, NULL) == -1)
    {    
        write(1, "Error getting current time\n", 30);
        exit(1);
    }
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}