#include "../includes/libft.h"

int	sep(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int	count_words(char *str, char *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!sep(str[i], set))
		{
			count++;
			while (str[i] && !sep(str[i], set))
				i++;
		}
		else
			i++;
	}
	return (count);
}