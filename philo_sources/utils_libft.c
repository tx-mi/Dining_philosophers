#include "philosophers.h"

int	ft_strncmp(const char *s1, const char *s2, long n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (n == 0)
		return (0);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (*str1 && *str2 && --n && *(str1) == *(str2))
	{
		str1++;
		str2++;
	}
	return (*(str1) - *(str2));
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long	ft_strlen(char *str)
{
	char *str_copy;

	str_copy = str;
	while (*str_copy)
		str_copy++;
	return (str_copy - str);
}

static int	ft_count_rank(int num)
{
	int	rank;

	rank = 1;
	while (num / 10)
	{
		rank *= 10;
		num /= 10;
	}
	return (rank);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	rank;
	int	num;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	rank = ft_count_rank(n);
	while (rank)
	{
		num = n / rank + '0';
		write(fd, &num, 1);
		n %= rank;
		rank /= 10;
	}
}
