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
	// int i = 0, j;
	// while (i < dim.x)
	// {
	// 	j = 0;
	// 	while (j < dim.y)
	// 	{
	// 		printf("%d,%d; ",(int)arr[i][j].x, (int)arr[i][j].y);
	// 		j++;
	// 	}
	// 	i++;
	// 	printf("\n");
	// }
	draw_fdf(mlx, arr, dim);
}