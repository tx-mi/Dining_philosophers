/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:28:54 by mwittenb          #+#    #+#             */
/*   Updated: 2022/01/14 22:57:14 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	philos_end(t_philo *philos, int nbr_philos, int i)
{
	if (current_time() - philos[i].time_of_last_meal
		>= philos[i].limit_of_life + 5)
	{
		sem_post(philos[i].death_sem);
		display_message(&philos[i], TYPE_DIED);
		i = -1;
		while (++i < nbr_philos)
			philos[i].dead = 1;
		return (1);
	}
	if (philos[i].data->nbr_of_meals && count_meals(philos))
	{
		sem_post(philos[i].death_sem);
		display_message(&philos[i], TYPE_OVER);
		i = -1;
		while (++i < nbr_philos)
			philos[i].dead = 1;
		return (1);
	}
	return (0);
}

void	*monitor(void *philosophers)
{
	t_philo	*philos;
	int		i;
	int		nbr_philos;

	philos = (t_philo *)philosophers;
	nbr_philos = philos[0].data->nbr_philos;
	while (1)
	{
		usleep(100);
		i = -1;
		while (++i < nbr_philos)
		{
			sem_wait(philos[i].death_sem);
			if (philos_end(philos, nbr_philos, i))
				return (NULL);
			sem_post(philos[i].death_sem);
		}
	}
	return (NULL);
}



void	*life_cycle(void *data)
{
	pthread_t	monik;
	t_philo		*philo;
	long		curtime;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		usleep(100);
	curtime = current_time();
	philo->time_of_last_meal = curtime;
	philo->start_time = curtime;
	if (pthread_create(&monik, NULL, &monitor, philo) != 0)
		return (NULL);
	while (!philo->dead)
	{
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	pthread_join(monik, NULL);
	return (NULL);
}

int	start_processes(t_data *data)
{
	int			i;
	void		*philo;

	
	i = 0;
	while (i < data->nbr_philos)
	{
		philo = (void*)(&data->philosophers[i]);
		data->philosophers[i].pid = fork();
		if (data->philosophers[i].pid < 0)
			return (1);
		else if (data->philosophers[i].pid == 0)
		{
			life_cycle(&data->philosophers[i]);
			exit(0);
		}
		usleep(100);
		i++;
	}
	return (0);
}
