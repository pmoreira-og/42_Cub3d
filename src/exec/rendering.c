#include "../../include/cub3d.h"

//? dir - fov/2 + x * step DIGITAL APPROACH
//? dir + fov/2 - (x + 0.5 ) * step MATH APPROACH

double	get_dot(t_dda *dda, t_player *p)
{
	return (dda->ray_dir_x * cos(p->direction) + dda->ray_dir_y * -sin(p->direction));
}

/// @brief Draw the map in 3d.
///
/// var[0] start_angle;
/// var[1] step;
/// var[2] perpDist;
// void	draw_map(t_game *g)
// {
// 	t_point	p;
// 	double	var[2];
// 	int		x;
// 	t_dda	dda;

// 	p.x = g->player.pos_x / g->scale;
// 	p.y = g->player.pos_y / g->scale;
// 	var[0] = g->player.direction + deg2rad(FOV / 2);
// 	x = -1;
// 	var[1] = deg2rad((double) FOV / (double) WIDTH);
// 	while (++x < WIDTH)
// 	{
// 		if (collider_dda(p, var[0] - ((x + 0.5) * var[1]), g, &dda) == -1)
// 			continue ;
// 		// dda.perp_dist = get_dot(&dda, &g->player);
// 		dda.perp_dist = get_perp_dist(dda.dist, var[0] - ((x + 0.5) * var[1]), g->player.direction);
// 		draw_section(g, &dda, x, &p);
// 	}
// 	mlx_put_image_to_window(g->mlx, g->win, g->bg.img, 0, 0);
// }
void player_update_dir_plane(t_player *p, double fov_deg)
{
	double	fov_rad;
	double	plane_mag;
	
	fov_rad = deg2rad(fov_deg);
	p->dir_x = cos(p->direction);
	p->dir_y = -sin(p->direction);
	plane_mag = tan(fov_rad / 2.0);
	p->plane_x = -p->dir_y * plane_mag;
	p->plane_y =  p->dir_x * plane_mag;
}

void draw_map(t_game *g)
{
	t_player	p;
	t_point		player;
	t_dda		dda;
	int			x;
	double		cameraX;

	p = g->player;
	p.pos_x /= g->scale;
	p.pos_y /= g->scale;
	player.x = g->player.pos_x / g->scale;
	player.y = g->player.pos_y / g->scale;
	x = 0;
	while (x < WIDTH)
	{
		cameraX = 2.0 * x / (double)WIDTH - 1.0;
		if (collider_dda(p, cameraX, g, &dda) == 0)
		{
			dda.perp_dist = dda.dist;
			draw_section(g, &dda, x, &player);
		}
		++x;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->bg.img, 0, 0);
}

//! ADAPT TO NEW WAY

// void	render_minimap(t_game *game)
// {
// 	t_point	a;
// 	double	angle;
// 	double	dist;
// 	// t_point	hit;

// 	dist = 0;
// 	a.x = game->player.pos_x;
// t_img_data	get_wall_text(t_game *g)
// {
// 	if (g->player.direction )
// 	g->player.direction
// }
// 	a.y = game->player.pos_y;
// 	angle = game->player.direction;
// 	while (1/* angle <= game->player.direction + 34 */)
// 	{
// 		dist = collider_angle(a, angle, WIDTH, game);
// 		// dist = collider_dda(a, angle, game, &hit);

// 		printf("[%f]dist:%f\n", angle, dist);
// 		if (dist != -1)
// 			draw(a, angle, WIDTH, game);
// 		angle++;
// 		break ;
// 	}
// 	mlx_put_image_to_window(game->mlx, game->win, game->bg->img, 0, 0);
// }

int	render_map(t_game *game)
{
	move_handler(game);
	if (!has_moved(game))
		return (1);
	game->player.direction = normalize_rad(game->player.direction);
	player_update_dir_plane(&game->player, FOV);
	draw_map(game);
	// render_minimap(game);
	return (1);
}
