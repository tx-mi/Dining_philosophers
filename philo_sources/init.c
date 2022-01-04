/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:46:34 by mwittenb          #+#    #+#             */
/*   Updated: 2022/01/04 22:50:42 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** if philos is last his first fork is fork with id 1
*/

static void	choose_fork(t_philo *philo, t_data *data)
{
	if (philo->id == data->nbr_philos)
	{
		philo->fork1 = &data->forks[(philo->id) % data->nbr_philos];
		philo->fork2 = &data->forks[philo->id - 1];
		return ;
	}
	philo->fork1 = &data->forks[philo->id - 1];
	philo->fork2 = &data->forks[philo->id];
}

int	init_data(int argc, char **argv, t_data *data)
{
	data->nbr_philos = ft_atoi(argv[1]);
	if (data->nbr_philos == 0)
		return (0);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_of_meals = ft_atoi(argv[5]);
	else
		data->nbr_of_meals = 0;
	pthread_mutex_init(&data->write_mutex, NULL);
	return (1);
}

int	init_forks(t_data *data)
{
	pthread_mutex_t	*mutexes;
	int				philos_nbr;

	philos_nbr = data->nbr_philos;
	mutexes = (pthread_mutex_t *)malloc(philos_nbr * sizeof(pthread_mutex_t));
	if (!mutexes)
		return (0);
	while (philos_nbr--)
		pthread_mutex_init(&mutexes[philos_nbr], NULL);
	data->forks = mutexes;
	return (1);
}

int	init_philosophers(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * data->nbr_philos);
	if (!philos)
		return (0);
	while (i < data->nbr_philos)
	{
		pthread_mutex_init(&philos[i].death_mutex, NULL);
		philos[i].id = i + 1;
		philos[i].dead = 0;
		philos[i].nbr_of_meals = 0;
		philos[i].time_of_last_meal = current_time();
		philos[i].limit_of_life = data->time_to_die;
		choose_fork(&philos[i], data);
		philos[i].data = data;
		i++;
	}
	data->philosophers = philos;
	return (1);
}

int	init(int argc, char **argv, t_data *data)
{
	if (!check_arguments(argc))
		return (0);
	if (!init_data(argc, argv, data))
		return (0);
	if (data->nbr_philos == 1)
	{
		printf("0\t 1 has taken a fork\n");
		ft_usleep(data->time_to_die);
		printf("%d\t 1 died\n", data->time_to_die + 1);
		pthread_mutex_destroy(&data->write_mutex);
		return (0);
	}
	if (!init_forks(data))
		return (0);
	if (!init_philosophers(data))
		return (0);
	return (1);
}
