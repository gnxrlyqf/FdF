#include "fdf.h"

fvector3_t **adjust_model(fvector3_t **arr, vector2_t dim)
{
	int i;
	int j;

	i = 0;
	while (i < dim.y)
	{
		j = 0;
		while (j < dim.x)
		{
			arr[i][j].x -= (dim.x / 2);	
			arr[i][j].y -= (dim.y / 2);
			arr[i][j].x *= 10;
			arr[i][j].y *= 10;
			arr[i][j].z *= 3;
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
				draw_line(p1, orig, mlx, dim);
			p2 = project_point(arr[++i][j]);
			draw_line(p1, p2, mlx, dim);
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
			draw_line(p1, p2, mlx, dim);
		}
		i++;
	}
}
	
int draw_fdf(ftl_t *vars_ig)
{
	mlx_clear_window(vars_ig->mlx.obj, vars_ig->mlx.window);
	draw_x(vars_ig->mlx, vars_ig->arr, vars_ig->dim);
	draw_y(vars_ig->mlx, vars_ig->arr, vars_ig->dim);
	return (0);
}