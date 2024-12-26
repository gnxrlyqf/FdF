#include "fdf.h"

void draw_line(vector2_t p1, vector2_t p2, mlx_instance_t mlx, t_data *img)
{
	vector2_t offset;
	vector2_t dir;
	int err1;
	int err2;

	(void)mlx;
	offset.x = abs(p2.x - p1.x);
	offset.y = abs(p2.y - p1.y);
	dir.x = (p1.x < p2.x) - (p1.x > p2.x);
	dir.y = (p1.y < p2.y) - (p1.y > p2.y);
	err1 = offset.x - offset.y;
	while (1)
	{
		my_mlx_pixel_put(img, p1.x, p1.y, 0x00FFFFFF);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		err2 = 2 * err1;
		if (err2 > -offset.y)
		{
			err1 -= offset.y;
			p1.x += dir.x;
		}
		if (err2 < offset.x)
		{
			err1 += offset.x;
			p1.y += dir.y;
		}
	}
}

void rotate_model(fvector3_t ***arr, float angle, fvector3_t (*f)(fvector3_t, float), vector2_t dim)
{
	int i;
	int j;

	i = -1;
	while (++i < dim.y)
	{
		j = -1;
		while (++j < dim.x)
			(*arr)[i][j] = f((*arr)[i][j], angle);
	}
}

vector2_t project_point(fvector3_t point)
{
	fvector3_t trans;
	vector2_t out;
	matrix2_t rot1 = init_m(init_v(1, 0, 0), init_v(0, 0, -1), init_v(0, -1, 0));
	trans = mul_matrix(point, rot1);
	trans = rotate_pitch(trans, -45);
	trans = rotate_roll(trans, 35.264);
	out.x = trans.x + 320;
	out.y = 240 - trans.y;
	return (out);
}

fvector3_t mul_matrix(fvector3_t vec, matrix2_t mat)
{
	fvector3_t out;

	out.x = vec.x * mat.x.x + vec.y * mat.x.y + vec.z * mat.x.z;
	out.y = vec.x * mat.y.x + vec.y * mat.y.y + vec.z * mat.y.z;
	out.z = vec.x * mat.z.x + vec.y * mat.z.y + vec.z * mat.z.z;

	return (out);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}