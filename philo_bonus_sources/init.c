/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:46:34 by mwittenb          #+#    #+#             */
/*   Updated: 2022/01/14 22:51:05 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
	sem_unlink(SEM_WRITE);
	data->write_sem = sem_open(SEM_WRITE, O_CREAT, 0777, 1);
	return (1);
}

int	init_forks(t_data *data)
{
	sem_unlink(SEM_FORKS);
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0777, data->nbr_philos);
	if (data->forks == SEM_FAILED)
		return (0);
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
	sem_unlink(SEM_DEATH);
	while (i < data->nbr_philos)
	{
		philos[i].id = i + 1;
		philos[i].dead = 0;
		philos[i].nbr_of_meals = 0;
		philos[i].time_of_last_meal = current_time();
		philos[i].limit_of_life = data->time_to_die;
		philos[i].data = data;
		philos[i].death_sem = sem_open(SEM_DEATH, O_CREAT, 0777, 1);
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
		sem_unlink(SEM_WRITE);
		sem_close(data->write_sem);
		return (0);
	}
	if (!init_forks(data))
		return (0);
	if (!init_philosophers(data))
		return (0);
	return (1);
}
