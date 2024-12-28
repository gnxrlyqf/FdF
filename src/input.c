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

int	mouse_motion(int x, int y, t_ftl *vars)
{
	static t_vector2	old;

	(void)y;
	if (vars->mouse_down)
		rotate_model(&(vars->arr), (x - old.x) * -.01, rotate_x, vars->dim);
	old.x = x;
	old.y = y;
	draw_fdf(vars);
	return (0);
}

int	mouse_down(int b, int x, int y, t_ftl *vars)
{
	(void)b;
	(void)x;
	(void)y;
	vars->mouse_down = 1;
	return (0);
}

int	mouse_up(int b, int x, int y, t_ftl *vars)
{
	(void)b;
	(void)x;
	(void)y;
	vars->mouse_down = 0;
	return (0);
}
