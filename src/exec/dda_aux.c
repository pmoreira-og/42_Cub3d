#include "../../include/cub3d.h"

void	init_struct(t_dda *dda, t_player *p, double cameraX)
{
	ft_bzero(dda, sizeof(t_dda));
	dda->ray_dir_x = p->dir_x + p->plane_x * cameraX;
	dda->ray_dir_y = p->dir_y + p->plane_y * cameraX;
	if (dda->ray_dir_x == 0.0)
		dda->dx = 1e30;
	else
		dda->dx = ft_abs(1.0 / dda->ray_dir_x);
	if (dda->ray_dir_y == 0.0)
		dda->dy = 1e30;
	else
		dda->dy = ft_abs(1.0 / dda->ray_dir_y);
	dda->map_x = (int) p->pos_x;
	dda->map_y = (int) p->pos_y;
	dda->hit = 0;
}

void	get_step(t_dda *dda, t_player *p)
{
	if (dda->ray_dir_x < 0.0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (p->pos_x - dda->map_x) * dda->dx;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - p->pos_x) * dda->dx;
	}
	if (dda->ray_dir_y < 0.0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (p->pos_y - dda->map_y) * dda->dy;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - p->pos_y) * dda->dy;
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

void	has_collided(t_dda *dda, t_game *game, t_player *p)
{
	if (game->matrix[(int)dda->map_y][(int)dda->map_x].type == WALL)
	{
		dda->hit = true;
		if (dda->side == 0)
			dda->dist = (dda->map_x - p->pos_x + (1 - dda->step_x) / 2.0)
				 / dda->ray_dir_x;
		else
			dda->dist = (dda->map_y - p->pos_y + (1 - dda->step_y) / 2.0)
				 / dda->ray_dir_y;
	}
}

void	save_hit_pos(t_dda *dda, t_player *p)
{
	double	hx;
	double	hy;

	hx = p->pos_x + dda->dist * dda->ray_dir_x;
	hy = p->pos_y + dda->dist * dda->ray_dir_y;
	dda->hit_point.x = hx;
	dda->hit_point.y = hy;
}
