/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:59 by mchetoui          #+#    #+#             */
/*   Updated: 2024/12/28 14:11:17 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fvector3	init_v(float x, float y, float z)
{
	t_fvector3	out;

	out.x = x;
	out.y = y;
	out.z = z;
	return (out);
}

t_fvector3	mul_matrix(t_fvector3 vec, t_matrix2 mat)
{
	t_fvector3	out;

	out.x = vec.x * mat.x.x + vec.y * mat.x.y + vec.z * mat.x.z;
	out.y = vec.x * mat.y.x + vec.y * mat.y.y + vec.z * mat.y.z;
	out.z = vec.x * mat.z.x + vec.y * mat.z.y + vec.z * mat.z.z;
	return (out);
}

int	max(int a, int b)
{
	return (a * (a >= b) + b * (a < b));
}

// int check_chars(char *str)
// {
// 	char *valid_chars;
// 	char *hex;
// 	char *hex1;
// 	char *hex2;
// 	char *cpy;

// 	valid_chars = "0123456789 ,-abcdefABCDEF\n";
// 	while (*str)
// 	{
// 		if (!ft_strchr(valid_chars, *str));
// 		if (*str == ',')

// 	}
// }