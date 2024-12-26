#include "fdf.h"

int mouse_motion(int x, int y, ftl_t *vars)
{
	static vector2_t pos_old;

	if (vars->mouse_down)
	{
		rotate_model(&(vars->arr), (x - pos_old.x) * .01, rotate_yaw);
		rotate_model(&(vars->arr), (y - pos_old.y) * .01, rotate_roll);
	}
	pos_old.x = x;
	pos_old.y = y;
	loop_hook(vars);
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