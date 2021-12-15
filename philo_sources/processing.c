/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:46:38 by mwittenb          #+#    #+#             */
/*   Updated: 2021/12/15 23:17:48 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*processing(void *data)
{
	t_philo	*philo;
	long	curtime;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		usleep(100);
	curtime = current_time();
	philo->time_of_last_meal = curtime;
	philo->start_time = curtime;
	while (!philo->dead)
	{
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
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
			pthread_mutex_lock(&philos[i].death_mutex);
			if (current_time() - philos[i].time_of_last_meal
				>= philos[i].limit_of_life + 5)
			{
				pthread_mutex_unlock(&philos[i].death_mutex);
				display_message(&philos[i], TYPE_DIED);
				i = -1;
				while (++i < nbr_philos)
					philos[i].dead = 1;
				return (NULL);
			}
			if (philos[i].data->nbr_of_meals && count_meals(philos))
			{
				display_message(&philos[i], TYPE_OVER);
				pthread_mutex_unlock(&philos[i].death_mutex);
				i = -1;
				while (++i < nbr_philos)
					philos[i].dead = 1;
				return (NULL);
			}
			pthread_mutex_unlock(&philos[i].death_mutex);
		}
	}
	return (NULL);
}

int	run_threads(t_data *data)
{
	pthread_t	*threads;
	pthread_t	monik;
	int			philos_nbr;
	int			i;

	philos_nbr = data->nbr_philos;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * philos_nbr);
	if (!threads)
		return (0);
	i = -1;
	while (++i < philos_nbr)
		pthread_create(&threads[i], NULL, processing,
			(void *)&data->philosophers[i]);
	pthread_create(&monik, NULL, monitor, (void *)data->philosophers);
	pthread_join(monik, NULL);
	data->tids = threads;
	return (1);
}
