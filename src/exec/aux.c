#include "../../include/cub3d.h"

void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}


