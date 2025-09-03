#include "../../include/cub3d.h"

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
			draw_section(g, &dda, x, &p);
		++x;
	}
}

//! ADAPT TO NEW WAY

void	render_minimap(t_game *game)
{
	t_player	p;

	p = game->player;
	p.pos_x /= game->scale;
	p.pos_y /= game->scale;
	fill_border(game);
	// draw_grid(game, &p);
	// draw_player(game, &p);
	// draw_rays(game, &p);
}

int	render_map(t_game *game)
{
	move_handler(game);
	if (!has_moved(game))
		return (1);
	game->player.direction = normalize_rad(game->player.direction);
	apply_bob_effect(&game->player, game);
	player_update_dir_plane(&game->player);
	draw_map(game);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg.img, 0, 0);
	return (1);
}
