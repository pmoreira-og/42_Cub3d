#include "../../include/cub3d.h"

bool	collider_dda(t_player p, double cameraX, t_game *g, t_dda *dda)
{
	init_struct(dda, &p, cameraX);
	get_step(dda, &p);
	while (!dda->hit)
	{
		next_step(dda);
		if (dda->map.x < 0 || dda->map.x >= g->map_width || dda->map.y < 0
			|| dda->map.y >= g->map_height)
			return (false);
		has_collided(dda, g, &p);
	}
	if (!isfinite(dda->perp_dist) || dda->perp_dist < 0.0)
		return (false);
	save_hit_pos(dda, &p);
	if (dda->perp_dist < 1e-6)
		dda->perp_dist = 1e-6;
	return (true);
}
