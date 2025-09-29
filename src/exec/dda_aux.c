/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:24:04 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/09/29 18:24:05 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_struct(t_dda *dda, t_player *p, double cameraX)
{
	ft_bzero(dda, sizeof(t_dda));
	dda->ray_dir.x = p->dir.x + p->plane.x * cameraX;
	dda->ray_dir.y = p->dir.y + p->plane.y * cameraX;
	if (dda->ray_dir.x == 0.0)
		dda->d.x = 1e30;
	else
		dda->d.x = ft_abs(1.0 / dda->ray_dir.x);
	if (dda->ray_dir.y == 0.0)
		dda->d.y = 1e30;
	else
		dda->d.y = ft_abs(1.0 / dda->ray_dir.y);
	dda->map.x = (int)p->pos.x;
	dda->map.y = (int)p->pos.y;
	dda->hit = 0;
}

void	get_step(t_dda *dda, t_player *p)
{
	if (dda->ray_dir.x < 0.0)
	{
		dda->step_x = -1;
		dda->side_dist.x = (p->pos.x - dda->map.x) * dda->d.x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist.x = (dda->map.x + 1.0 - p->pos.x) * dda->d.x;
	}
	if (dda->ray_dir.y < 0.0)
	{
		dda->step_y = -1;
		dda->side_dist.y = (p->pos.y - dda->map.y) * dda->d.y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist.y = (dda->map.y + 1.0 - p->pos.y) * dda->d.y;
	}
}

void	next_step(t_dda *dda)
{
	if (dda->side_dist.x < dda->side_dist.y)
	{
		dda->side_dist.x += dda->d.x;
		dda->map.x += dda->step_x;
		dda->side = 0;
	}
	else
	{
		dda->side_dist.y += dda->d.y;
		dda->map.y += dda->step_y;
		dda->side = 1;
	}
}

void	has_collided(t_dda *dda, t_game *game, t_player *p)
{
	if (game->matrix[(int)dda->map.y][(int)dda->map.x].type == WALL)
	{
		dda->hit = true;
		if (dda->side == 0)
			dda->perp_dist = (dda->map.x - p->pos.x + (1 - dda->step_x) / 2.0)
				/ dda->ray_dir.x;
		else
			dda->perp_dist = (dda->map.y - p->pos.y + (1 - dda->step_y) / 2.0)
				/ dda->ray_dir.y;
	}
}

void	save_hit_pos(t_dda *dda, t_player *p)
{
	double	hx;
	double	hy;

	hx = p->pos.x + dda->perp_dist * dda->ray_dir.x;
	hy = p->pos.y + dda->perp_dist * dda->ray_dir.y;
	dda->hit_point.x = hx;
	dda->hit_point.y = hy;
}
