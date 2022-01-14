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
}
