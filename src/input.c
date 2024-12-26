#include "fdf.h"

int mouse_motion(int x, int y, ftl_t *vars)
{
	static vector2_t old;

	if (vars->mouse_down)
	{
		rotate_model(&(vars->arr), (x - old.x) * -.01, rotate_yaw, vars->dim);
		// rotate_model(&(vars->arr), (y - old.y) * .01, rotate_pitch, vars->dim);
	}
	old.x = x;
	old.y = y;
	draw_fdf(vars);
	return (0);
}

int mouse_down(int b, int x, int y, ftl_t *vars)
{
	(void)b;
	(void)x;
	(void)y;
	vars->mouse_down = 1;
	return (0);
}

int mouse_up(int b, int x, int y, ftl_t *vars)
{
	(void)b;
	(void)x;
	(void)y;
	vars->mouse_down = 0;
	return (0);
}