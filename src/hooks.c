/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:27 by mchetoui          #+#    #+#             */
/*   Updated: 2024/12/28 14:10:27 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_motion(int x, int y, t_vars *vars)
{
	static t_vector2	old;

	if (vars->left_down)
		rotate_model(&(vars->arr), (x - old.x) * -.01, rotate_x, vars->dim);
	else if (vars->right_down)
		translate_model(&(vars->arr), x - old.x, y - old.y, vars->dim);
	old.x = x;
	old.y = y;
	draw_fdf(vars);
	return (0);
}

int	mouse_down(int b, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (b == 1)
		vars->left_down = 1;
	if (b == 3)
		vars->right_down = 1;
	return (0);
}

int	mouse_up(int b, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (b == 1)
		vars->left_down = 0;
	if (b == 3)
		vars->right_down = 0;
	return (0);
}
int close_window(t_vars *vars)
{
	free_model(vars->arr, vars->dim.y);
	mlx_destroy_window(vars->mlx.obj, vars->mlx.window);
	mlx_destroy_display(vars->mlx.obj);
	free(vars->mlx.obj);
	// mlx_destroy_image(vars->mlx, (vars->img).img);
	exit(0);
	return (0);	
}