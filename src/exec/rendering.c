/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:26:25 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/09/29 18:31:15 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	manager(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_win_mouse, game);
	mlx_hook(game->win, 2, 1L << 0, key_press_manager, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_manager, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_handler, game);
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

static void	draw_flashlight(t_game *g)
{
	sprite_to_bg(&g->bg, &g->hand[g->player.flash_on], (t_cord){440, 440},
		(t_cord){WIDTH - 440, HEIGHT - 440});
	if (g->mini.show)
		sprite_to_bg(&g->bg, &g->flash[g->player.flash_on], (t_cord){189, 51},
			(t_cord){g->mini.offset, HEIGHT - 100});
}

static void	render_menu(t_game *game)
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
	hide_mouse(game);
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
		draw_flashlight(game);
		if (game->mini.show)
			render_minimap(game->mini);
		mlx_put_image_to_window(game->mlx, game->win, game->bg.img, 0, 0);
	}
	return (1);
}
