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
		if (dda->map_x < 0 || dda->map_x >= (int)g->map_width
			|| dda->map_y < 0 || dda->map_y >= (int)g->map_height)
			return (-1.0);
		has_collided(dda, g, &p);
	}
	if (!isfinite(dda->dist) || dda->dist < 0.0)
		return (-1.0);
	save_hit_pos(dda, &p);
	if (dda->dist < 1e-6)
		dda->dist = 1e-6;
	return (0);
}
