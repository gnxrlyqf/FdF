#include <mlx.h>
#include "fdf.h"

void print_list(list_t *list)
{
	list_t *curr;

	curr = list;
	while (curr)
	{
		printf("%s", curr->str);
		curr = curr->next;
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	mlx_instance_t mlx;
	mlx.obj = mlx_init();
	mlx.window = mlx_new_window(mlx.obj, 640, 480, "fdf");
	int fd = open_file(av[1]);
	list_t *head = parse_file(fd);
	vector2_t dim;
	dim.x = list_len(head);
	dim.y = count_words(head->str, " ");
	fvector3_t **arr = convert_to_coords(head);
	arr = adjust_model(arr, dim);
	ftl_t vars_ig;
	vars_ig.arr = arr;
	vars_ig.dim = dim;
	vars_ig.mlx = mlx;
	vars_ig.mouse_down = 0;
	mlx_hook(mlx.window, 4, (1L<<2), mouse_down, &vars_ig);
	mlx_hook(mlx.window, 5, (1L<<3), mouse_up, &vars_ig);
	mlx_hook(mlx.window, 6, (1L<<6), mouse_motion, &vars_ig);
	// mlx_loop_hook(mlx.obj, loop_hook, &vars_ig);
	mlx_loop(mlx.obj);
}