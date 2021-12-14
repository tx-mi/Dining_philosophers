#include "philosophers.h"

static char	*get_message(int type)
{
	if (type == TYPE_EAT)
		return (" is eating\n");
	else if (type == TYPE_SLEEP)
		return (" is sleeping\n");
	else if (type == TYPE_FORK)
		return (" has taken a fork\n");
	else if (type == TYPE_THINK)
		return (" is thinking\n");
	else if (type == TYPE_OVER)
		return ("Every philosopher ate at least ");
	return (" died\n");
}

void	display_message(t_philo *philo, int type)
{
	static int	done = 0;

	pthread_mutex_lock(&philo->data->write_mutex);
	if (!done)
	{
		ft_putnbr_fd(current_time() - philo->start_time, 1);
		write(1, "\t", 1);
		if (type != TYPE_OVER)
			ft_putnbr_fd(philo->id, 1);
		if (type == TYPE_DIED || type == TYPE_OVER)
			done = 1;
		write(1, get_message(type), ft_strlen(get_message(type)));
		if (type == TYPE_OVER)
		{
			ft_putnbr_fd(philo->data->nbr_of_meals, 1);
			write(1, " times\n", 7);
		}
	}
	pthread_mutex_unlock(&philo->data->write_mutex);
}
