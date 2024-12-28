/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:23 by mchetoui          #+#    #+#             */
/*   Updated: 2024/12/28 14:10:25 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color	int_to_color(int color)
{
	t_color	out;

	out.a = (color >> 24) & 0xFF;
	out.r = (color >> 16) & 0xFF;
	out.g = (color >> 8) & 0xFF;
	out.b = color & 0xFF;
	return (out);
}

int	get_grad(int p1color, int p2color, int step, int steps)
{
	t_color	argb1;
	t_color	argb2;
	t_color	grad;
	t_color	out;

	argb1 = int_to_color(p1color);
	argb2 = int_to_color(p2color);
	grad.a = (argb2.a - argb1.a) / (float)steps;
	grad.r = (argb2.r - argb1.r) / (float)steps;
	grad.g = (argb2.g - argb1.g) / (float)steps;
	grad.b = (argb2.b - argb1.b) / (float)steps;
	out.a = argb1.a + round(grad.a * step);
	out.r = argb1.r + round(grad.r * step);
	out.g = argb1.g + round(grad.g * step);
	out.b = argb1.b + round(grad.b * step);
	return ((out.a << 24) | (out.r << 16) | (out.g << 8) | out.b);
}
int peak(t_vertex3 **arr, t_vector2 dim)
{
	int i;
	int j;
	int peak;

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

t_vertex3	**adjust_model(t_vertex3 **arr, t_vector2 dim)
{
	int	i;
	int	j;
	int max_height;
	float scale;

	max_height = peak(arr, dim);
	scale = (SIZE - 100) / (float)max(max(dim.x, dim.y), max_height);
	i = 0;
	while (i < dim.y)
	{
		j = 0;
		while (j < dim.x)
		{
			arr[i][j].pos.x -= (dim.x / 2) - .5 * (dim.x % 2 == 0);
			arr[i][j].pos.y -= (dim.y / 2) - .5 * (dim.y % 2 == 0);
			arr[i][j].pos.z -= max_height / 4;
			arr[i][j].pos.x *= scale;
			arr[i][j].pos.y *= scale;
			arr[i][j].pos.z *= scale / 2;
			j++;
		}
		i++;
	}
	return (arr);
}

t_vertex2	project_point(t_vertex3 point)
{
	t_fvector3	transform;
	t_vertex2	out;
	t_matrix2	cam;

	cam.x = init_v(1, 0, 0);
	cam.y = init_v(0, 0, -1);
	cam.z = init_v(0, -1, 0);
	transform = mul_matrix(point.pos, cam);
	transform = rotate_y(transform, -45);
	transform = rotate_z(transform, 35.264);
	out.pos.x = transform.x + (SIZE / 2);
	out.pos.y = (SIZE / 2) - transform.y;
	out.col = point.col;
	return (out);
}
