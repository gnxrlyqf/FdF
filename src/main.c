/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:32 by mchetoui          #+#    #+#             */
/*   Updated: 2024/12/28 14:10:53 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"

int	main(int ac, char **av)
{
	t_ftl	vars;
	int		fd;
	t_list	*head;
	int		size;

	if (ac != 2)
		return (1);
	fd = open_file(av[1]);
	head = parse_file(fd);
	vars.dim.x = count_words(head->str, " ");
	vars.dim.y = list_len(head);
	vars.arr = convert_to_coords(head);
	vars.arr = adjust_model(vars.arr, vars.dim, &size);
	vars.mlx.obj = mlx_init();
	vars.mlx.window = mlx_new_window(vars.mlx.obj, MAX, MAX, "fdf");
	vars.mouse_down = 0;
	draw_fdf(&vars);
	mlx_hook(vars.mlx.window, 4, (1L << 2), mouse_down, &vars);
	mlx_hook(vars.mlx.window, 5, (1L << 3), mouse_up, &vars);
	mlx_hook(vars.mlx.window, 6, (1L << 6), mouse_motion, &vars);
	mlx_loop(vars.mlx.obj);
}
