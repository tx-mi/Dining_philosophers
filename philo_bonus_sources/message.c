/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:47:00 by mwittenb          #+#    #+#             */
/*   Updated: 2022/01/18 20:28:36 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

void	display_message(t_data *data, int type)
{
	static int	done = 0;

	sem_wait(data->write_sem);
	if (!done)
	{
		ft_putnbr_fd(current_time() - data->start_time, 1);
		write(1, "\t", 1);
		if (type != TYPE_OVER)
			ft_putnbr_fd(data->id, 1);
		if (type == TYPE_DIED || type == TYPE_OVER)
			done = 1;
		write(1, get_message(type), ft_strlen(get_message(type)));
		if (type == TYPE_OVER)
		{
			ft_putnbr_fd(data->nbr_of_meals, 1);
			write(1, " times\n", 7);
		}
	}
	sem_post(data->write_sem);
}
