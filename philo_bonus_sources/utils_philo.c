/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:18:56 by mwittenb          #+#    #+#             */
/*   Updated: 2022/01/04 21:57:54 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	check_arguments(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf(" ____________________________________________________ \n");
		printf("|            Please enter 4 or 5 arguments           |\n");
		printf("|____________________________________________________|\n");
		printf("|             [1][Number of datasophers]            |\n");
		printf("|             [2][Time to die]                       |\n");
		printf("|             [3][Time to eat]                       |\n");
		printf("|             [4][Time to sleep]                     |\n");
		printf("|             [5][Number of meals]                   |\n");
		printf("|____________________________________________________|\n");
		return (0);
	}
	return (1);
}

long	current_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (long)tv.tv_sec + (long)tv.tv_usec / 1000;
	return (res);
}

void	ft_usleep(int ms)
{
	long	time;

	time = current_time();
	usleep(ms * 920);
	while (current_time() < time + (long)ms)
		usleep(ms * 3);
}

int	count_meals(t_data *data)
{
	int	i;
	int	nbr_philos;

	i = -1;
	nbr_philos = data->nbr_philos;
	while (++i < nbr_philos)
	{
		// if (data->nbr_of_meals < data->nbr_of_meals)
		// 	return (0);
	}
	return (0);
}
