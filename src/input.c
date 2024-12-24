#include "fdf.h"

int mouse_hook(int b, int x, int y, fvector3_t ***arr)
{
	printf("%d", b);
	if (b == 1)
	{
		// rotate_model(arr, acos(x / 640) + asin(x / 640), rotate_yaw);
		// rotate_model(arr, acos(y / 480) + asin(y / 480), rotate_pitch);
	}
	(void)arr;
	(void)x;
	(void)y;
	return (0);
}