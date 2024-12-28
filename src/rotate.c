/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:54 by mchetoui          #+#    #+#             */
/*   Updated: 2024/12/28 14:11:06 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_model(t_vertex3 ***arr, float angle,
t_fvector3 (*f)(t_fvector3, float), t_vector2 dim)
{
	int	i;
	int	j;

	i = -1;
	while (++i < dim.y)
	{
		j = -1;
		while (++j < dim.x)
			(*arr)[i][j].pos = f((*arr)[i][j].pos, angle);
	}
}

t_fvector3	rotate_x(t_fvector3 point, float angle)
{
	t_matrix2	rot;

	rot.x = init_v(cos(angle), -sin(angle), 0);
	rot.y = init_v(sin(angle), cos(angle), 0);
	rot.z = init_v(0, 0, 1);
	return (mul_matrix(point, rot));
}

t_fvector3	rotate_y(t_fvector3 point, float angle)
{
	t_matrix2	rot;

	rot.x = init_v(cos(angle), 0, sin(angle));
	rot.y = init_v(0, 1, 0);
	rot.z = init_v(-sin(angle), 0, cos(angle));
	return (mul_matrix(point, rot));
}

t_fvector3	rotate_z(t_fvector3 point, float angle)
{
	t_matrix2	rot;

	rot.x = init_v(1, 0, 0);
	rot.y = init_v(0, cos(angle), -sin(angle));
	rot.z = init_v(0, sin(angle), cos(angle));
	return (mul_matrix(point, rot));
}
