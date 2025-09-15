#include "../../include/cub3d.h"

double	ft_min(double n1, double n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}

int	get_pixel(t_img_data *img, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x > img->width || y > img->height)
		return (0);
	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}
