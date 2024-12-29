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

t_fvector3	init_v3(float x, float y, float z)
{
	t_fvector3	out;

	out.x = x;
	out.y = y;
	out.z = z;
	return (out);
}

t_fvector3	mul_matrix3(t_fvector3 vec, t_matrix3 mat)
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

t_color	int_to_color(int color)
{
	t_color	out;

	out.a = (color >> 24) & 0xFF;
	out.r = (color >> 16) & 0xFF;
	out.g = (color >> 8) & 0xFF;
	out.b = color & 0xFF;
	return (out);
}

int	peak(t_vertex3 **arr, t_vector2 dim)
{
	int	i;
	int	j;
	int	peak;

	i = -1;
	peak = 0;
	while (++i < dim.y)
	{
		j = -1;
		while (++j < dim.x)
			if (arr[i][j].pos.z > peak)
				peak = arr[i][j].pos.z;
	}
	return (peak);
}
