/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 23:36:54 by mchetoui          #+#    #+#             */
/*   Updated: 2024/12/28 13:55:27 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi_ptr(char **str)
{
	int		sign;
	int		result;
	char	*cpy;

	result = 0;
	sign = 1;
	cpy = *str;
	while (*cpy == ' ' || (*cpy >= 9 && *cpy <= 13))
		cpy++;
	if (*cpy == '-' || *cpy == '+')
	{
		sign *= (44 - *cpy);
		cpy++;
	}
	while (*cpy >= '0' && *cpy <= '9')
	{
		result = result * 10 + (*cpy - '0');
		cpy++;
	}
	*str = cpy;
	return (result * sign);
}
