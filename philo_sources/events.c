/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:47:20 by mwittenb          #+#    #+#             */
/*   Updated: 2022/01/14 22:46:40 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	display_message(philo, TYPE_FORK);
	pthread_mutex_lock(philo->fork2);
	pthread_mutex_lock(&philo->death_mutex);
	display_message(philo, TYPE_FORK);
}

void	eating(t_philo *philo)
{
	display_message(philo, TYPE_EAT);
	philo->time_of_last_meal = current_time();
	philo->nbr_of_meals++;
	pthread_mutex_unlock(&philo->death_mutex);
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
