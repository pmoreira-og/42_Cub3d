#include "../../include/cub3d.h"

void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 13 || y < 0 || y >= 6)
		return ((void) printf_fd(2, "bugou essa poha\n"));
	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}


