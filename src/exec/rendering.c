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
	t_dda		dda;
	int			x;
	double		camera_x;

	x = 0;
	while (x < WIDTH)
	{
		camera_x = 2.0 * x / (double)WIDTH - 1.0;
		if (collider_dda(g->player, camera_x, g, &dda) == 0)
			draw_section(g, &dda, x, &g->player);
		++x;
	}
}

//! ADAPT TO NEW WAY

void	render_minimap(t_game *game)
{
	colorblock_to_bg(game, 0, (t_cord){game->mini.width, game->mini.height}, (t_cord){game->mini.offset, game->mini.offset});
	// fill_border(game);
	// draw_grid(game, &p);
	// draw_player(game, &p);
	// draw_rays(game, &p);
}

int	render_map(t_game *game)
{
	if (game->scene == MENU)
	{
		// this will be an animation using fps
		// to run between the animation frames
		mlx_put_image_to_window(game->mlx, game->win, game->menu.img, 0, 0);
	}
	else if (game->scene == GAME)
	{
		move_handler(game);
		if (!has_moved(game))
			return (1);
		game->player.direction = normalize_rad(game->player.direction);
		apply_bob_effect(&game->player, game);
		player_update_dir_plane(&game->player);
		draw_map(game);
		render_minimap(game);
		sprite_to_bg(game, &game->hand, (t_cord){560, 560}, (t_cord){800, 520});
		mlx_put_image_to_window(game->mlx, game->win, game->bg.img, 0, 0);
	}
	return (1);
}
