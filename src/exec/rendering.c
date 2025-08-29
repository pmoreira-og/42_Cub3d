#include "../../include/cub3d.h"

//? dir - fov/2 + x * step DIGITAL APPROACH
//? dir + fov/2 - (x + 0.5 ) * step MATH APPROACH

void	player_update_dir_plane(t_player *p)
{
	p->dir_x = cos(p->direction);
	p->dir_y = -sin(p->direction);
	p->plane_x = -p->dir_y * p->plane_mag;
	p->plane_y = p->dir_x * p->plane_mag;
}

void	draw_map(t_game *g)
{
	t_player	p;
	t_dda		dda;
	int			x;
	double		camera_x;

	p = g->player;
	p.pos_x /= g->scale;
	p.pos_y /= g->scale;
	x = 0;
	while (x < WIDTH)
	{
		camera_x = 2.0 * x / (double)WIDTH - 1.0;
		if (collider_dda(p, camera_x, g, &dda) == 0)
		{
			dda.perp_dist = dda.dist;
			draw_section(g, &dda, x, &p);
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
	player_update_dir_plane(&game->player);
	draw_map(game);
	// render_minimap(game);
	return (1);
}
