#include "fdf.h"

float window_size(vector2_t dim)
{
	int bigger;
	
	bigger = max(dim.x, dim.y);
	return ((MAX - 200) / bigger);
}

vertex3_t **adjust_model(vertex3_t **arr, vector2_t dim, int *size)
{
	int i;
	int j;

	(void)size;
	i = 0;
	printf("%f\n", window_size(dim));
	while (i < dim.y)
	{
		j = 0;
		while (j < dim.x)
		{
			arr[i][j].pos.x -= dim.x / 2;
			arr[i][j].pos.y -= dim.y / 2;
			arr[i][j].pos.z -= dim.y / 2;
			arr[i][j].pos.x *= window_size(dim);
			arr[i][j].pos.y *= window_size(dim);
			arr[i][j].pos.z *= 1;
			j++;
		}
		i++;
	}
	return (arr);
}

void draw_x(mlx_instance_t mlx, vertex3_t **arr, vector2_t dim, t_data *img)
{
	int i;
	int j;
	vertex2_t p1;
	vertex2_t p2;

	j = 0;
	while (j < dim.x)
	{
		i = 0;
		while (i + 1 < dim.y)
		{
			p1 = project_point(arr[i][j]);
			p2 = project_point(arr[++i][j]);
			draw_line(p1, p2, mlx, img);
		}
		j++;
	}
}

void draw_y(mlx_instance_t mlx, vertex3_t **arr, vector2_t dim, t_data *img)
{
	int i;
	int j;
	vertex2_t p1;
	vertex2_t p2;

	i = 0;
	while (i < dim.y)
	{
		j = 0;
		while (j + 1 < dim.x)
		{
			p1 = project_point(arr[i][j]);
			p2 = project_point(arr[i][++j]);
			draw_line(p1, p2, mlx, img);
		}
		i++;
	}
}
	
int draw_fdf(ftl_t *vars_ig)
{
	t_data img;

	img.img = mlx_new_image(vars_ig->mlx.obj, MAX, MAX);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	draw_x(vars_ig->mlx, vars_ig->arr, vars_ig->dim, &img);
	draw_y(vars_ig->mlx, vars_ig->arr, vars_ig->dim, &img);
	mlx_put_image_to_window(vars_ig->mlx.obj, vars_ig->mlx.window, img.img, 0, 0);
	return (0);
}