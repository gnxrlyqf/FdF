#include "fdf.h"

fvector3_t **adjust_model(fvector3_t **arr, vector2_t dim)
{
	int i;
	int j;

	i = 0;
	while (i < dim.x)
	{
		j = 0;
		while (j < dim.y)
		{
			arr[i][j].x -= (dim.x / 2);	
			arr[i][j].y -= (dim.y / 2);
			arr[i][j].x *= 10;
			arr[i][j].y *= 10;
			arr[i][j].z *= 20;
			j++;
		}
		i++;
	}
	return (arr);
}

void draw_x(mlx_instance_t mlx, fvector3_t **arr, vector2_t dim)
{
	int i;
	int j;
	vector2_t p1 = {0, 0};
	vector2_t p2 = {0, 0};
	vector2_t orig = {0, 0};

	j = 0;
	while (j < dim.y)
	{
		i = 0;
		while (i + 1 < dim.x)
		{
			p1 = project_point(arr[i][j]);
			if (!i && !j)
				draw_line(p1, orig, mlx, 0x00FF0000);
			p2 = project_point(arr[++i][j]);
			draw_line(p1, p2, mlx, 0x00FFFFFF);
		}
		j++;
	}
}

void draw_y(mlx_instance_t mlx, fvector3_t **arr, vector2_t dim)
{
	int i;
	int j;
	vector2_t p1;
	vector2_t p2;

	i = 0;
	while (i < dim.x)
	{
		j = 0;
		while (j + 1 < dim.y)
		{
			p1 = project_point(arr[i][j]);
			p2 = project_point(arr[i][++j]);
			draw_line(p1, p2, mlx, 0x00FFFFFF);
		}
		i++;
	}
}
	
void draw_fdf(mlx_instance_t mlx, fvector3_t **arr, vector2_t dim)
{
	arr = adjust_model(arr, dim);
	draw_x(mlx, arr, dim);
	draw_y(mlx, arr, dim);
	mlx_loop(mlx.obj);
}