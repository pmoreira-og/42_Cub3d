#include "../../include/cub3d.h"

/// @brief Get absolute value of a double type number.
double	ft_abs(double nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	return (nbr);
}

double	collider_dda(t_player p, double cameraX, t_game *g, t_dda *dda)
{
	init_struct(dda, &p, cameraX);
	get_step(dda, &p);
	while (!dda->hit)
	{
		next_step(dda);
		if (dda->map_x < 0 || dda->map_x >= (int)g->map_width || dda->map_y < 0
			|| dda->map_y >= (int)g->map_height)
			return (-1.0);
		has_collided(dda, g, &p);
	}
	if (!isfinite(dda->perp_dist) || dda->perp_dist < 0.0)
		return (-1.0);
	save_hit_pos(dda, &p);
	if (dda->perp_dist < 1e-6)
		dda->perp_dist = 1e-6;
	return (0);
}

/// @brief Raycasting collision checker based on trigonometric circle angles.
/// @param angle Trigonometric circle based angle in rads.
/// @param max_dist Max distance of the line to check collision.
/// @param game Main struct.
/// @return 
t_cord    collider_angle(double angle, double max_dist,
    t_game *game, double cord_x, double cord_y)
{
    double    inc[2];
    int        i;

    inc[0] = cos(angle);
    inc[1] = -sin(angle);
	i = -1;
    while (++i <= (int)max_dist)
    {
		if (get_pixel(&game->bg, cord_x, cord_y) == 0) 
        	return ((t_cord){-1,-1});
		put_pixel(&game->bg, cord_x, cord_y, 0x00FF00);
        cord_x += inc[0];
        cord_y += inc[1];
    }

    return ((t_cord){floor(cord_x), floor(cord_y)});
}

void    draw_line(t_game *g, t_cord start, t_cord end)
{
    double    d[2];
    double    steps;
    int       i;

    d[0] = end.x - start.x;
    d[1] = end.y - start.y;
    if (ft_abs(d[0]) >= ft_abs(d[1]))
        steps = ft_abs(d[0]);
    else
        steps = ft_abs(d[1]);
    d[0] /= steps;
    d[1] /= steps;
    i = -1;
    while (++i <= steps)
    {
		if (get_pixel(&g->bg, start.x, start.y) == 0) 
        	return ;
        put_pixel(&g->bg, start.x, start.y, 0x00FF00);
        start.x += d[0];
        start.y += d[1];
    }
}
