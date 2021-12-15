/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:47:13 by mwittenb          #+#    #+#             */
/*   Updated: 2021/12/15 21:47:14 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_move_from_space(char **s)
{
	while (**s == '\f' || **s == '\r' || **s == '\t'
		|| **s == '\n' || **s == '\v' || **s == ' ')
		(*s)++;
}

static int	ft_count_num(char *s)
{
	int	i;

	i = 0;
	while (ft_isdigit(s[i]))
		i++;
	return (i);
}

static int	ft_convert_to_int(char *str, int size)
{
	unsigned int	result;
	int				rank;
	int				i;

	result = 0;
	rank = 1;
	i = size - 1;
	while (i >= 0 && ft_isdigit(str[i]))
	{
		result += (int)(str[i] - '0') *rank;
		rank *= 10;
		i--;
	}
	return (result);
}

static int	ft_overflow_check(unsigned int num, int sign)
{
	if ((num > 2147483648 && sign == -1))
		return (0);
	if (num > 2147483647 && sign == 1)
		return (-1);
	return (num);
}

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned int	size;
	unsigned int	result;
	char			*s;

	sign = 1;
	result = 0;
	s = (char *)str;
	ft_move_from_space(&s);
	if (!ft_strncmp(s, "-2147483648", 11))
		return (-2147483648);
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	size = ft_count_num(s);
	result = ft_convert_to_int(s, size);
	result = ft_overflow_check(result, sign);
	return (result * sign);
}
