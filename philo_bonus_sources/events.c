/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:47:20 by mwittenb          #+#    #+#             */
/*   Updated: 2022/01/18 21:18:10 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	take_forks(t_data *data)
{
	sem_wait(data->forks);
	display_message(data, TYPE_FORK);
	sem_wait(data->forks);
	display_message(data, TYPE_FORK);
	sem_wait(data->death_sem);
}

void	eating(t_data *data)
{
	display_message(data, TYPE_EAT);
	data->time_of_last_meal = current_time();
	sem_post(data->death_sem);
	ft_usleep(data->time_to_eat);
	sem_post(data->eat_sem);
	data->meals++;
	sem_post(data->forks);
	sem_post(data->forks);
}

void	sleeping(t_data *data)
{
	display_message(data, TYPE_SLEEP);
	ft_usleep(data->time_to_sleep);
}
