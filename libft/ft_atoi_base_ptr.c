/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base_ptr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:54:22 by mchetoui          #+#    #+#             */
/*   Updated: 2024/12/28 13:57:06 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	convert(char **str, char *cpy, char *base)
{
	int	result;
	int	i;
	int	blen;

	result = 0;
	blen = 16;
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
	int		i;
	char	*base1;
	char	*base2;
	char	*cpy;

	base1 = "0123456789ABCDEF";
	base2 = "0123456789abcdef";
	if (!*str)
		return (0);
	cpy = *str + 3;
	i = 0;
	while (i++ < 6)
		if (cpy[i] >= 97 && cpy[i] <= 102)
			return (convert(str, cpy, base2));
	return (convert(str, cpy, base1));
}
