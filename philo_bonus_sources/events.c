/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:47:20 by mwittenb          #+#    #+#             */
/*   Updated: 2022/01/14 22:57:13 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	display_message(philo, TYPE_FORK);
	sem_wait(philo->data->forks);
	display_message(philo, TYPE_FORK);
	sem_wait(philo->death_sem);
}

void	eating(t_philo *philo)
{
	display_message(philo, TYPE_EAT);
	philo->time_of_last_meal = current_time();
	philo->nbr_of_meals++;
	sem_post(philo->death_sem);
	ft_usleep(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
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
