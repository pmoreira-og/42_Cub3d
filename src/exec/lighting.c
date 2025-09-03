#include "../../include/cub3d.h"

double	get_light(int y)
{
	double	light;
	double	step;

	light = 1;
	step = (2.0 / HEIGHT);
	if (y >= (HEIGHT / 2))
		y = HEIGHT - y;
	light -= y * step;
	if (light < 0.05)
		light = 0.05;
	return (light);
}

int	apply_light(int color, double light)
{
	int	r;
	int	g;
	int	b;

	r = (((color >> 16 & 0xFF)) * light);
	g = (((color >> 8 & 0xFF)) * light);
	b = (((color & 0xFF)) * light);
	return (get_color(r, g, b));
}

int	get_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
