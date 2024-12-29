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
	scale = (SIZE - (SIZE / 10)) / (float)max(max(dim.x, dim.y), max_height);
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

t_vertex2	project_point(t_vertex3 point, int type, float scale)
{
	if (type == 1)
		return (project_isometric(point, scale));
	// if (type == 2)
	// 	return (project_perspective(point));
	return(project_isometric(point, scale));
}


t_vertex2	project_isometric(t_vertex3 point, float scale)
{
	t_fvector3	transform;
	t_vertex2	out;
	t_matrix3	cam;

	cam.x = init_v3(1, 0, 0);
	cam.y = init_v3(0, 0, -1);
	cam.z = init_v3(0, -1, 0);
	point.pos.x *= scale;
	point.pos.y *= scale;
	point.pos.z *= scale;
	transform = mul_matrix3(point.pos, cam);
	transform = rotate_y(transform, -45);
	transform = rotate_z(transform, 35.264);
	out.pos.x = transform.x + (SIZE / 2);
	out.pos.y = (SIZE / 2) - transform.y;
	out.col = point.col;
	return (out);
}
