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

t_vertex3	**adjust_model(t_vertex3 **arr, t_vector2 dim)
{
	int		i;
	int		j;
	int		max_height;
	float	scale;

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
	t_vertex2	out;

	point.pos.x *= scale;
	point.pos.y *= scale;
	point.pos.z *= scale;
	if (type == 1)
		out.pos = project_isometric(point.pos);
	if (type == 2)
		out.pos = project_perspective(point.pos);
	out.col = point.col;
	return (out);
}

t_vector2	project_perspective(t_fvector3 point)
{
	t_fvector3	cam;
	t_fvector3	plane;
	t_matrix3	transform;
	t_vector2	out;

	cam = init_v3(-120, 0, -120);
	plane = init_v3(0, 0, -110);
	point = rotate_x(point, 90);
	point = rotate_y(point, 45);
	plane = rotate_z(plane, 35.264);
	point.x -= cam.x;
	point.y -= cam.y;
	point.z -= cam.z;
	transform.x = init_v3(1, 0, plane.x / plane.z);
	transform.y = init_v3(0, 1, plane.y / plane.z);
	transform.z = init_v3(0, 0, 1 / plane.z);
	point = mul_matrix3(point, transform);
	out.x = point.x / point.z + (SIZE / 2);
	out.y = (SIZE / 2) - point.y / point.z;
	return (out);
}

t_vector2	project_isometric(t_fvector3 point)
{
	t_vector2	out;
	t_matrix3	cam;

	cam.x = init_v3(1, 0, 0);
	cam.y = init_v3(0, 0, -1);
	cam.z = init_v3(0, -1, 0);
	point = mul_matrix3(point, cam);
	point = rotate_y(point, -45);
	point = rotate_x(point, 35.264);
	out.x = point.x + (SIZE / 2);
	out.y = (SIZE / 2) - point.y;
	return (out);
}
