#include "../../include/cub3d.h"

//! Probably gonna need 1 more param to get the right wall text.

/// @brief Draw the vertical section of the wall
/// @param g Game struct.
/// @param perpWallDist Dist between the player and the object.
/// @param x X position on the screen to draw.
void	draw_section(t_game *g, double perpWallDist, int x)
{
	int	start;
	int	end;
	int	height;
	int	y;

	if (perpWallDist <= 0.000001)
		perpWallDist = 0.000001;
	height = (int) (HEIGHT/ perpWallDist);
	start = -height / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	y = -1;
	while (++y < start)
		put_pixel(g->bg, x, y, g->ceiling_color);
	while(++y <= end)
		put_pixel(g->bg, x, y, 0x00FF00);
	while(++y < HEIGHT)
		put_pixel(g->bg, x, y, g->floor_color);
}

double	get_perp_dist(double hyp, double angle, double p_angle)
{
	return (hyp * cos(angle - p_angle));
}
