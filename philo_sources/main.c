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

int	main(int argc, char **argv)
{
	t_data	*data;
	(void)argv;

	if (check_arguments(argc))
		return (1);
	// init data
	// init forks/mutexes
	// init philosophers
	// init threads
	// process
}
