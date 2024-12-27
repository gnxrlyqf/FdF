#include "fdf.h"

int max(int a, int b)
{
	return (a * (a >= b) + b * (a < b));
}

color_t int_to_color(int color)
{
	color_t out;

	out.a = (color >> 24) & 0xFF;
	out.r = (color >> 16) & 0xFF;
	out.g = (color >> 8) & 0xFF;
	out.b = color & 0xFF;

	return (out);
}

int color_to_int(color_t color)
{
	return ((color.a << 24) | (color.r << 16) | (color.g << 8) | color.b);
}

int get_grad(int p1color, int p2color, int step, int steps)
{
	color_t argb1;
	color_t argb2;
	color_t grad;
	color_t out;

	argb1 = int_to_color(p1color);
	argb2 = int_to_color(p2color);

	grad.a = (argb2.a - argb1.a) / (float)steps;
	grad.r = (argb2.r - argb1.r) / (float)steps;
	grad.g = (argb2.g - argb1.g) / (float)steps;
	grad.b = (argb2.b - argb1.b) / (float)steps;

    out.a = argb1.a + round(grad.a * step);
    out.r = argb1.r + round(grad.r * step);
    out.g = argb1.g + round(grad.g * step);
    out.b = argb1.b + round(grad.b * step);

	return (color_to_int(out));
}

void draw_line(vertex2_t p1, vertex2_t p2, mlx_instance_t mlx, t_data *img)
{
	vector2_t offset;
	vector2_t dir;
	vector2_t err;
	int step;

	(void)mlx;
	offset.x = abs(p2.pos.x - p1.pos.x);
	offset.y = abs(p2.pos.y - p1.pos.y);
	dir.x = (p1.pos.x < p2.pos.x) - (p1.pos.x > p2.pos.x);
	dir.y = (p1.pos.y < p2.pos.y) - (p1.pos.y > p2.pos.y);
	err.x = offset.x - offset.y;
	step = -1;
	while (1)
	{
		p1.color = get_grad(p1.color, p2.color, ++step, max(offset.x, offset.y));
		my_mlx_pixel_put(img, p1.pos.x, p1.pos.y, p1.color);
		if (p1.pos.x == p2.pos.x && p1.pos.y == p2.pos.y)
			break ;
		err.y = 2 * err.x;
		if (err.y > -offset.y)
		{
			err.x -= offset.y;
			p1.pos.x += dir.x;
		}
		if (err.y < offset.x)
		{
			err.x += offset.x;
			p1.pos.y += dir.y;
		}
	}
}

void rotate_model(vertex3_t ***arr, float angle, fvector3_t (*f)(fvector3_t, float), vector2_t dim)
{
	int i;
	int j;

	i = -1;
	while (++i < dim.y)
	{
		j = -1;
		while (++j < dim.x)
			(*arr)[i][j].pos = f((*arr)[i][j].pos, angle);
	}
}

vertex2_t project_point(vertex3_t point)
{
	fvector3_t trans;
	vertex2_t out;
	matrix2_t rot1 = init_m(init_v(1, 0, 0), init_v(0, 0, -1), init_v(0, -1, 0));

	trans = mul_matrix(point.pos, rot1);
	trans = rotate_pitch(trans, -45);
	trans = rotate_roll(trans, 35.264);
	out.pos.x = trans.x + 240;
	out.pos.y = 240 - trans.y;
	out.color = point.color;
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