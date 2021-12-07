#include "philosophers.h"

/*
** if philos is last his first fork is fork with id 1
*/

static void	choose_fork(t_philo *philo, t_data *data)
{
	if (philo->id == data->nbr_philos)
	{
		philo->fork2 = &data->forks[philo->id];
		philo->fork1 = &data->forks[(philo->id + 1) % data->nbr_of_meals];
		return	;
	}
	philo->fork1 = &data->forks[philo->id];
	philo->fork2 = &data->forks[philo->id + 1];
}

void	init_data(t_data *data, int argc, char **argv)
{
	data = (t_data *)malloc(sizeof(t_data));
	// if (!data)
	// 	terminate(ERR_DATA);
	data->nbr_philos = ft_atoi(argv[1]);
	if (data->nbr_philos == 0)
		return ;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_of_meals = ft_atoi(argv[5]);
}

void	init_forks(t_data *data)
{
	pthread_mutex_t	*mutexes;
	int				philos_nbr;


	philos_nbr = data->nbr_philos;
	mutexes = (pthread_mutex_t *)malloc(philos_nbr * sizeof(pthread_mutex_t));
	// if (!mutexes)
	// 	terminate(ERR_FORKS);
	while (philos_nbr--)
		pthread_mutex_init(&mutexes[philos_nbr], NULL);
	data->forks = mutexes;
}

void	init_philosophers(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * data->nbr_philos);
	// if (!philos)
		// terminate(ERR_PHILOS_INIT);
	while (i < data->nbr_philos)
	{
		philos[i].id = i;
		philos[i].nbr_of_meals = 0;
		philos[i].time_of_last_meal = 0;
		philos[i].limit_of_life = data->time_to_die;
		choose_fork(&philos[i], data);
		i++;
	}
	data->philosophers = philos;
}
