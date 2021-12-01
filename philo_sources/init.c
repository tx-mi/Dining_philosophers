#include "philosophers.h"

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
