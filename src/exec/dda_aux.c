#include "../../include/cub3d.h"

void	init_struct(t_dda *dda, t_point *start, t_game *game, double angle)
{
	ft_bzero(dda, sizeof(t_dda));
	dda->ray_dir_x = cos(angle * (PI / 180));
	dda->ray_dir_y = -sin(angle * (PI / 180));
	dda->dx = ft_abs(1.0 / dda->ray_dir_x);
	dda->dy = ft_abs(1.0 / dda->ray_dir_y);
	dda->map_x = (start->x / game->scale);
	dda->map_y = (start->y / game->scale);
}

void	has_collided(t_dda *dda, t_game *game, t_point *start)
{
	if (game->matrix[(int)dda->map_y][(int)dda->map_x].type == WALL)
	{
		dda->hit = true;
		if (dda->side == 0)
			dda->perp_wall_dist = (dda->map_x - start->x / game->scale
					+ (1 - dda->step_x) / 2) / dda->ray_dir_x;
		else
			dda->perp_wall_dist = (dda->map_y - start->y / game->scale
					+ (1 - dda->step_y) / 2) / dda->ray_dir_y;
	}
}

void	next_step(t_dda *dda)
{
	if (dda->side_dist_x < dda->side_dist_y)
	{
		dda->side_dist_x += dda->dx;
		dda->map_x += dda->step_x;
		dda->side = 0;
	}
	else
	{
		dda->side_dist_y += dda->dy;
		dda->map_y += dda->step_y;
		dda->side = 1;
	}
}

void	save_hit_pos(t_dda *dda, t_point *hit, t_game *game, t_point *start)
{
	if (dda->side == 0)
	{
		hit->x = dda->map_x * game->scale;
		hit->y = start->y + dda->perp_wall_dist * dda->ray_dir_y * game->scale;
	}
	else
	{
		hit->x = start->x + dda->perp_wall_dist * dda->ray_dir_x * game->scale;
		hit->y = dda->map_y * game->scale;
	}
}

void	get_step(t_dda *dda, t_point *start, t_game *game)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (start->x / game->scale - dda->map_x)
			* dda->dx;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = ((dda->map_x + 1.0) - start->x / game->scale)
			* dda->dx;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (start->y / game->scale - dda->map_y) * dda->dy;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = ((dda->map_y + 1.0) - start->y / game->scale)
			* dda->dy;
	}
}