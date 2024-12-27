#include "../includes/libft.h"

int	idx(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
		if (c == base[i++])
			return (i - 1);
	return (-1);
}

int	convert(char **str, char *cpy, char *base, int blen)
{
	int	result;
	int	i;

	result = 0;
	while (*cpy)
	{
		i = idx(*cpy, base);
		if (i == -1)
			break ;
		result = result * blen + i;
		cpy++;
	}
	*str = cpy;
	return (result);
}

int	ft_atoi_base_ptr(char **str)
{
	int	sign;
	char *base;
	char *cpy;
	
	base = "0123456789ABCDEF";
	if (!*str)
		return (0);
	cpy = *str + 3;
	sign = 1;
	while (*cpy == ' ' || (*cpy >= 9 && *cpy <= 13))
		cpy++;
	// while (*cpy == '-' || *cpy == '+')
	// {
	// 	sign *= (44 - *cpy);
	// 	cpy++;
	// }
	return (convert(str, cpy, base, 16) * sign);
}