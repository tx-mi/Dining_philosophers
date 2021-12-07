#include "philosophers.h"

void	terminate(const char *error)
{
	printf("%s\n", error);
	exit(1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
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
