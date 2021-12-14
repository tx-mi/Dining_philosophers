#include "philosophers.h"

void	destroy_and_clear(t_data *data)
{
	int		i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nbr_philos)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	if (data->philosophers)
		free(data->philosophers);
}

void	completion_threads(t_data *data)
{
	int	philos_nbr;

	philos_nbr = data->nbr_philos;
	while (philos_nbr--)
		pthread_join(data->tids[philos_nbr], NULL);
}

void	finish_program(t_data *data)
{
	completion_threads(data);
	destroy_and_clear(data);
}