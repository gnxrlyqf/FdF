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
	return (color_to_int(out));
}

t_vertex3	**adjust_model(t_vertex3 **arr, t_vector2 dim, int *size)
{
	int	i;
	int	j;

	(void)size;
	i = 0;
	while (i < dim.y)
	{
		j = 0;
		while (j < dim.x)
		{
			arr[i][j].pos.x -= dim.x / 2;
			arr[i][j].pos.y -= dim.y / 2;
			arr[i][j].pos.z -= dim.y / 2;
			arr[i][j].pos.z *= 5;
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
	out.pos.x = transform.x + (MAX / 2);
	out.pos.y = (MAX / 2) - transform.y;
	out.col = point.col;
	return (out);
}
