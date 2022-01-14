/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:47:16 by mwittenb          #+#    #+#             */
/*   Updated: 2022/01/04 23:14:30 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
