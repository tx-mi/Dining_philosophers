/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 18:18:52 by mwittenb          #+#    #+#             */
/*   Updated: 2022/01/14 22:51:23 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (!init(argc, argv, &data))
		return (-1);
	if (!start_processes(&data))
		return (-1);
	sem_wait(data.simulation);
	sem_unlink(SEM_SIMULATION);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORKS);
	sem_close(data.simulation);
	sem_close(data.death_sem);
	sem_close(data.forks);
	sem_close(data.write_sem);
}
