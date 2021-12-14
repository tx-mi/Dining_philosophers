#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!init(argc, argv, &data))
		return (-1);
	if (!run_threads(&data))
		return (-1);
	finish_program(&data);
}
