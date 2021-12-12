#include "philosophers.h"

static int	check_arguments(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf(" ____________________________________________________ \n");
		printf("|            Please enter 4 or 5 arguments           |\n");
		printf("|____________________________________________________|\n");
		printf("|             [1][Number of philosophers]            |\n");
		printf("|             [2][Time to die]                       |\n");
		printf("|             [3][Time to eat]                       |\n");
		printf("|             [4][Time to sleep]                     |\n");
		printf("|             [5][Number of meals]                   |\n");
		printf("|____________________________________________________|\n");
		return (1);
	}
	return(0);
}

void	run_threads(t_data *data)
{
	pthread_t	*threads;
	int			philos_nbr;

	philos_nbr = data->nbr_philos;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * philos_nbr);
	while(philos_nbr--)
		pthread_create(&threads[philos_nbr], NULL, processing,
					(void *)&data->philosophers[philos_nbr]);
	data->tids = threads;
}

void	*processing(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (check_arguments(argc))
		return (1);
	data = init_data(argc, argv);
	if (!data)
		return (1);
	init_forks(data);
	init_philosophers(data);
	run_threads(data);
}
