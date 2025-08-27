#include "../../include/cub3d.h"

/// @brief Get absolute value of a double type number.
double	ft_abs(double nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	return (nbr);
}

//! Adapt to minimap function
// static bool	check_colision(double x0, double y0, t_game *game, t_point **hit)
// {
// 	int	x;
// 	int	y;

// 	x = (int)(x0 / game->scale);
// 	y = (int)(y0 / game->scale);
// 	(void) hit;
// 	if (x >= 0 && x < (int )game->map_width
// 		&& y >= 0 && y < (int )game->map_height)
// 	{
// 		if (game->matrix[y][x].type == WALL)
// 		{
// 			return (true);
// 		}
// 	}
// 	return (false);
// }

double	collider_dda(t_point start, double angle, t_game *g, t_dda *dda)
{
	init_struct(dda, &start, angle);
	get_step(dda, &start);
	while (!dda->hit)
	{
		next_step(dda);
		if (dda->map_x < 0 || dda->map_x >= (int)g->map_width
			|| dda->map_y < 0 || dda->map_y >= (int)g->map_height)
			return (-1.0);
		has_collided(dda, g);
	}
	if (!isfinite(dda->dist) || dda->dist < 0.0)
		return (-1.0);
	save_hit_pos(dda, &start);
	return (dda->dist);
}
