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
	t_vars	vars;

	if (ac > 3 || ac == 1)
		throw_err(2, NULL, NULL);
	if (SIZE > 1080)
		throw_err(7, NULL, NULL);
	vars = init_vars(parse_file(open_file(av[1])), av[2]);
	draw_fdf(&vars);
	mlx_key_hook(vars.mlx.window, key_hook, &vars);
	mlx_hook(vars.mlx.window, 4, (1L << 2), mouse_down, &vars);
	mlx_hook(vars.mlx.window, 5, (1L << 3), mouse_up, &vars);
	mlx_hook(vars.mlx.window, 6, (1L << 6), mouse_motion, &vars);
	mlx_hook(vars.mlx.window, 17, 0, close_window, &vars);
	mlx_loop(vars.mlx.obj);
}

t_vars	init_vars(t_list *head, char *type)
{
	t_vars	vars;

	vars.dim.x = count_words(head->str, " ");
	vars.dim.y = list_len(head);
	vars.arr = adjust_model(convert_to_coords(head), vars.dim);
	vars.mlx.obj = mlx_init();
	vars.mlx.window = mlx_new_window(vars.mlx.obj, SIZE, SIZE, "fdf");
	vars.left_down = 0;
	vars.right_down = 0;
	vars.offset.x = 0;
	vars.offset.y = 0;
	vars.scale = 1;
	if (type)
		vars.type = ft_atoi_ptr(&type);
	else
		vars.type = 1;
	free_t_list(&head);
	return (vars);
}
