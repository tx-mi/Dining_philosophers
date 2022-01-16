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

static int	is_philo_end(t_data *data)
{
	if (current_time() - data->time_of_last_meal
		>= data->time_to_die + 5)
	{
		sem_post(data->death_sem);
		sem_post(data->simulation);
		display_message(data, TYPE_DIED);
		data->dead = 1;
		exit(0);
	}
	if (data->nbr_of_meals && count_meals(data))
	{
		sem_post(data->death_sem);
		sem_post(data->simulation);
		display_message(data, TYPE_OVER);
		data->dead = 1;
		exit(0);
	}
	return (0);
}

void	*monitor(void *datum)
{
	t_data	*data;
	int		i;
	int		nbr_philos;

	data = (t_data *)datum;
	nbr_philos = data->nbr_philos;
	while (1)
	{
		usleep(100);
		i = -1;
		while (++i < nbr_philos)
		{
			sem_wait(data->death_sem);
			if (is_philo_end(data))
				return (NULL);
			sem_post(data->death_sem);
		}
	}
	return (NULL);
}

void	*life_cycle(t_data *data)
{
	pthread_t	monik;
	long		curtime;

	if (data->id % 2 == 0)
		usleep(100);
	curtime = current_time();
	data->time_of_last_meal = curtime;
	data->start_time = curtime;
	if (pthread_create(&monik, NULL, &monitor, data) != 0)
		exit(1);
	while (!data->dead)
	{
		take_forks(data);
		eating(data);
		sleeping(data);
		display_message(data, TYPE_THINK);
	}
	pthread_join(monik, NULL);
	return (NULL);
}

int	start_processes(t_data *data)
{
	int			i;
	int			var;
	
	i = -1;
	data->pids = (pid_t *)malloc(sizeof(pid_t) * data->nbr_philos);
	while (++i < data->nbr_philos)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			return (1);
		else if (data->pids[i] == 0)
		{
			data->id = i + 1;
			life_cycle(data);
			exit(0);
		}
		usleep(100);
	}
	waitpid(-1, &var, 0);
	i = 0;
	if (var == 0)
	{
		while (i < data->nbr_philos)
			kill(data->pids[i++], SIGTERM);
	}
	return (0);
}
