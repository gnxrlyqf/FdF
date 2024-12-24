#include "fdf.h"

void draw_line(vector2_t p1, vector2_t p2, mlx_instance_t mlx, int color)
{
	vector2_t offset;
	vector2_t dir;
	int err1;
	int err2;

	offset.x = abs(p2.x - p1.x);
	offset.y = abs(p2.y - p1.y);
	dir.x = -(p1.x > p2.x) + (p1.x < p2.x);
	dir.y = -(p1.y > p2.y) + (p1.y < p2.y);
	err1 = offset.x - offset.y;
	while (1)
	{
		mlx_pixel_put(mlx.obj, mlx.window, p1.x, p1.y, color);
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

fvector3_t mul_matrix(fvector3_t vec, matrix2_t mat)
{
	fvector3_t out;

	out.x = vec.x * mat.x.x + vec.y * mat.x.y + vec.z * mat.x.z;
	out.y = vec.x * mat.y.x + vec.y * mat.y.y + vec.z * mat.y.z;
	out.z = vec.x * mat.z.x + vec.y * mat.z.y + vec.z * mat.z.z;

	return (out);
}

fvector3_t rotate_yaw(fvector3_t point, float angle)
{
	fvector3_t x;
	fvector3_t y;
	fvector3_t z;
	matrix2_t rot;

	x = init_v(cos(angle), -sin(angle), 0);
	y = init_v(sin(angle), cos(angle), 0);
	z = init_v(0, 0, 1);
	rot = init_m(x, y, z);
	return(mul_matrix(point, rot));
}

void rotate_model(fvector3_t ***arr, float angle, fvector3_t (*f)(fvector3_t, float))
{
	int i;
	int j;

	i = -1;
	while ((*arr)[++i])
	{
		j = -1;
		while ((*arr)[i][++j].z != INT_MAX)
			(*arr)[i][j] = f((*arr)[i][j], angle);
	}
}

fvector3_t rotate_pitch(fvector3_t point, float angle)
{
	fvector3_t x;
	fvector3_t y;
	fvector3_t z;
	matrix2_t rot;

	x = init_v(cos(angle), 0, sin(angle));
	y = init_v(0, 1, 0);
	z = init_v(-sin(angle), 0, cos(angle));
	rot = init_m(x, y, z);
	return(mul_matrix(point, rot));
}

fvector3_t rotate_roll(fvector3_t point, float angle)
{
	fvector3_t x;
	fvector3_t y;
	fvector3_t z;
	matrix2_t rot;

	x = init_v(1, 0, 0);
	y = init_v(0, cos(angle), -sin(angle));
	z = init_v(0, sin(angle), cos(angle));
	rot = init_m(x, y, z);
	return(mul_matrix(point, rot));
}

vector2_t project_point(fvector3_t point)
{
	fvector3_t trans;
	vector2_t out;
	matrix2_t rot1 = init_m(init_v(1, 0, 0), init_v(0, 0, 1), init_v(0, 1, 0));
	trans = mul_matrix(point, rot1);
	trans = rotate_pitch(trans, -45);
	trans = rotate_roll(trans, 35.264);
	// trans = mul_matrix(trans, rot4, 1);
	out.x = trans.x + 320;
	out.y = 240 - trans.y;
	return (out);
}

matrix2_t init_m(fvector3_t x, fvector3_t y, fvector3_t z)
{
	matrix2_t out;

	out.x = x;
	out.y = y;
	out.z = z;

	return (out);
}

fvector3_t init_v(float x, float y, float z)
{
	fvector3_t out;

	out.x = x;
	out.y = y;
	out.z = z;

	return (out);
}