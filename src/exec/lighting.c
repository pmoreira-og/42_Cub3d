#include "../../include/cub3d.h"

double	get_light(int y, t_player *p)
{
	double	light;
	double	step;

	if (p->flash_on)
		light = 0.95;
	else
		light = 0.7;
	step = (2.0 / HEIGHT);
	if (y > ((HEIGHT / 2) + (p->vertical_view)))
		y = (HEIGHT + (p->vertical_view)) - y;
	else
		y -= p->vertical_view;
	light -= y * step;
	if (light < 0.05)
		light = 0.05;
	if (light > 1)
		light = 1;
	return (light);
}

int	apply_light(int color, double light)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16 & 0xFF)) * light);
	g = (int)(((color >> 8 & 0xFF)) * light);
	b = (int)(((color & 0xFF)) * light);
	return (get_color(r, g, b));
}

int	get_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
