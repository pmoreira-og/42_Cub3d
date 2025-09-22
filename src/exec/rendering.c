#include "../../include/cub3d.h"

static void	player_update_dir_plane(t_player *p)
{
	p->dir.x = cos(p->direction);
	p->dir.y = -sin(p->direction);
	p->plane.x = -p->dir.y * p->plane_mag;
	p->plane.y = p->dir.x * p->plane_mag;
}

static void	draw_map(t_game *g)
{
	t_dda	dda;
	int		x;
	double	camera_x;

	x = 0;
	while (x < WIDTH)
	{
		camera_x = 2.0 * x / (double)WIDTH - 1.0;
		if (collider_dda(g->player, camera_x, g, &dda))
			draw_section(g, &dda, x, &g->player);
		++x;
	}
}

static void	draw_flashlight(t_game *game)
{
	if (game->player.flash_on)
		sprite_to_bg(&game->bg, &game->hand[0], (t_cord){560, 560},
			(t_cord){800, 520});
	else
		sprite_to_bg(&game->bg, &game->hand[1], (t_cord){560, 560},
			(t_cord){800, 520});
}

void	render_menu(t_game *game)
{
	static bool	clockwise;
	static int	i;

	if (time_passed(500))
	{
		if (i == 3 || i == 0)
			clockwise = !clockwise;
		if (clockwise)
			i++;
		else
			i--;
		mlx_put_image_to_window(game->mlx, game->win, game->menu[i].img, 0, 0);
	}
}

int	render_map(t_game *game)
{
	if (game->scene == MENU)
		render_menu(game);
	else if (game->scene == GAME)
	{
		move_handler(game);
		if (!has_moved(game) && !has_changed(game))
			return (1);
		game->player.direction = normalize_rad(game->player.direction);
		apply_bob_effect(&game->player, game);
		player_update_dir_plane(&game->player);
		draw_map(game);
		if (game->mini.show)
			render_minimap(game->mini);
		draw_flashlight(game);
		mlx_put_image_to_window(game->mlx, game->win, game->bg.img, 0, 0);
	}
	return (1);
}
