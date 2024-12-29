/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:08 by mchetoui          #+#    #+#             */
/*   Updated: 2024/12/28 14:10:21 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	if (x >= 0 && x < SIZE && y >= 0 && y < SIZE)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_line(t_vertex2 p1, t_vertex2 p2, t_data *img)
{
	t_vector2	offset;
	t_vector2	dir;
	t_vector2	err;
	int			step;

	offset.x = abs(p2.pos.x - p1.pos.x);
	offset.y = abs(p2.pos.y - p1.pos.y);
	dir.x = (p1.pos.x < p2.pos.x) - (p1.pos.x > p2.pos.x);
	dir.y = (p1.pos.y < p2.pos.y) - (p1.pos.y > p2.pos.y);
	err.x = offset.x - offset.y;
	step = -1;
	while (1)
	{
		p1.col = get_grad(p1.col, p2.col, ++step, max(offset.x, offset.y));
		my_mlx_pixel_put(img, p1.pos.x, p1.pos.y, p1.col);
		if (p1.pos.x == p2.pos.x && p1.pos.y == p2.pos.y)
			break ;
		err.y = 2 * err.x;
		err.x = err.x - offset.y * (err.y > -offset.y);
		err.x = err.x + offset.x * (err.y < offset.x);
		p1.pos.x = p1.pos.x + dir.x * (err.y > -offset.y);
		p1.pos.y = p1.pos.y + dir.y * (err.y < offset.x);
	}
}

void	draw_x(t_vars *vars, t_data *img)
{
	int			i;
	int			j;
	t_vertex2	p1;
	t_vertex2	p2;

	j = 0;
	while (j < vars->dim.x)
	{
		i = 0;
		while (i + 1 < vars->dim.y)
		{
			p1 = project_point(vars->arr[i][j], vars->type, vars->scale);
			p2 = project_point(vars->arr[++i][j], vars->type, vars->scale);
			p1.pos.x += vars->offset.x;
			p1.pos.y += vars->offset.y;
			p2.pos.x += vars->offset.x;
			p2.pos.y += vars->offset.y;
			draw_line(p1, p2, img);
		}
		j++;
	}
}

void	draw_y(t_vars *vars, t_data *img)
{
	int			i;
	int			j;
	t_vertex2	p1;
	t_vertex2	p2;

	i = 0;
	while (i < vars->dim.y)
	{
		j = 0;
		while (j + 1 < vars->dim.x)
		{
			p1 = project_point(vars->arr[i][j], vars->type, vars->scale);
			p2 = project_point(vars->arr[i][++j], vars->type, vars->scale);
			p1.pos.x += vars->offset.x;
			p1.pos.y += vars->offset.y;
			p2.pos.x += vars->offset.x;
			p2.pos.y += vars->offset.y;
			draw_line(p1, p2, img);
		}
		i++;
	}
}

int	draw_fdf(t_vars *vars)
{
	t_data	img;

	img.img = mlx_new_image(vars->mlx.obj, SIZE, SIZE);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	draw_x(vars, &img);
	draw_y(vars, &img);
	mlx_put_image_to_window(vars->mlx.obj, vars->mlx.window, img.img, 0, 0);
	mlx_destroy_image(vars->mlx.obj, img.img);
	return (0);
}
