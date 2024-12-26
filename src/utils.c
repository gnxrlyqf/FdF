#include "fdf.h"

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