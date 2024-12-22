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

fvector3_t mul_matrix(fvector3_t vec, matrix2_t mat, float coeff)
{
	fvector3_t out;

	out.x = (vec.x * mat.x.x + vec.y * mat.x.y + vec.z * mat.x.z) * coeff;
	out.y = (vec.x * mat.y.x + vec.y * mat.y.y + vec.z * mat.y.z) * coeff;
	out.z = (vec.x * mat.z.x + vec.y * mat.z.y + vec.z * mat.z.z) * coeff;

	return (out);
}

vector2_t project_point(fvector3_t point)
{
	fvector3_t trans;
	vector2_t out;
	// matrix2_t rot1 = init_m(init_v(1, 0, 0), init_v(0, 0, -1), init_v(0, 1, 0));
	matrix2_t rot1 = init_m(init_v(0, -1, 0), init_v(0, 0, 1), init_v(-1, 0, 0));
	// matrix2_t rot2 = init_m(init_v(sqrt(3), 0, -sqrt(3)), init_v(1, 2, 1), init_v(sqrt(2), -sqrt(2), sqrt(2)));
	// matrix2_t rot3 = init_m(init_v(1, 0, 0), init_v(0, cos(35.264), sin(35.264)), init_v(0, -sin(35.264), cos(35.264)));
	matrix2_t rot2 = init_m(init_v(cos(45), 0, -sin(45)), init_v(0, 1, 0), init_v(sin(45), 0, cos(45)));
	trans = mul_matrix(point, rot1, 1);
	// trans = mul_matrix(point, rot3, 1);
	trans = mul_matrix(trans, rot2, 1);
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