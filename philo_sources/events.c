#include "philosophers.h"


void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	display_message(philo, TYPE_FORK);
    pthread_mutex_lock(philo->fork2);
	display_message(philo, TYPE_FORK);
}

void	eating(t_philo *philo)
{
	display_message(philo, TYPE_EAT);
    philo->time_of_last_meal = current_time();
    philo->nbr_of_meals++;
    ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->fork2);
    pthread_mutex_unlock(philo->fork1);
}

void	sleeping(t_philo *philo)
{
	display_message(philo, TYPE_SLEEP);
    ft_usleep(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	display_message(philo, TYPE_THINK);
}
