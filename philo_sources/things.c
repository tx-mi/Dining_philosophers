#include "philosophers.h"

void	take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->fork1);
    printf("philo %d take first fork\n", philo->id + 1);
    pthread_mutex_lock(philo->fork2);
    printf("philo %d take second fork\n", philo->id + 1);
}

void	eating(t_philo *philo)
{
    printf("philo %d ate\n", philo->id + 1);
    philo->nbr_of_meals++;
    usleep(philo->time_to_eat * 1000);
    pthread_mutex_unlock(philo->fork2);
    pthread_mutex_unlock(philo->fork1);
}

void	sleeping(t_philo *philo)
{
    usleep(philo->time_to_sleep * 1000);
    printf("philo %d is thinking\n", philo->id + 1);
}

void	thinking(t_philo *philo)
{
    printf("philo %d is thinking\n", philo->id + 1);
}
