/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:24:06 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/09/29 18:24:07 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	player_update_dir_plane(t_player *p)
{
	p->dir.x = cos(p->direction);
	p->dir.y = -sin(p->direction);
	p->plane.x = -p->dir.y * p->plane_mag;
	p->plane.y = p->dir.x * p->plane_mag;
}

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
