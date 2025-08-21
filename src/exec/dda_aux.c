#include "../../include/cub3d.h"

void	init_struct(t_dda *dda, t_point *start, double angle)
{
	ft_bzero(dda, sizeof(t_dda));
	dda->ray_dir_x = cos(angle * (PI / 180));
	dda->ray_dir_y = -sin(angle * (PI / 180));
	if (dda->ray_dir_x == 0.0)
		dda->dx = 1e30;
	else
		dda->dx = ft_abs(1.0 / dda->ray_dir_x);
	if (dda->ray_dir_y == 0.0)
		dda->dy = 1e30;
	else
		dda->dy = ft_abs(1.0 / dda->ray_dir_y);
	dda->map_x = (int) floor(start->x);
	dda->map_y = (int) floor(start->y);
}

void	get_step(t_dda *dda, t_point *start)
{
	if (dda->ray_dir_x < 0.0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (start->x - dda->map_x) * dda->dx;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - start->x) * dda->dx;
	}
	if (dda->ray_dir_y < 0.0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (start->y - dda->map_y) * dda->dy;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - start->y) * dda->dy;
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

void	has_collided(t_dda *dda, t_game *game)
{
	if (game->matrix[(int)dda->map_y][(int)dda->map_x].type == WALL)
	{
		dda->hit = true;
		if (dda->side == 0)
			dda->perp_wall_dist = dda->side_dist_x - dda->dx;
		else
			dda->perp_wall_dist = dda->side_dist_y - dda->dy;
	}
}

void	save_hit_pos(t_dda *dda, t_point *hit, t_point *start)
{
	double	hx;
	double	hy;

	hx = start->x + dda->perp_wall_dist * dda->ray_dir_x;
	hy = start->y + dda->perp_wall_dist * dda->ray_dir_y;
	hit->x = hx;
	hit->y = hy;
}
