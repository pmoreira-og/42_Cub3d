/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:11:39 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/09/29 18:11:39 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	load_assets(t_game *g);
static bool	load_walls(t_game *g);
static bool	get_img(t_game *game, int width, int height);

/// @brief initialized all windows and images needed for rendering
/// @param game struct that will be used to run the game
/// @return true on success, false on failure
bool	setup_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (printf_fd(2, M_MLXINITF), false);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, TITLE);
	if (!game->win)
		return (printf_fd(2, M_MLXWINDF), false);
	if (!load_assets(game))
		return (printf_fd(2, M_ERRO M_INVXPM), false);
	if (!load_walls(game))
		return (printf_fd(2, M_ERRO M_INVXPM), false);
	if (!get_img(game, WIDTH, HEIGHT))
		return (false);
	game->bg.width = WIDTH;
	game->bg.height = HEIGHT;
	game->player.flash_fov = deg2rad(FLASH_FOV);
	game->player.cos_flash = cos(game->player.flash_fov / 2);
	return (true);
}

static bool	load_assets(t_game *g)
{
	if (!get_sprite_data(g, &g->menu[0], MAIN_MENU "1.xpm"))
		return (false);
	if (!get_sprite_data(g, &g->menu[1], MAIN_MENU "2.xpm"))
		return (false);
	if (!get_sprite_data(g, &g->menu[2], MAIN_MENU "3.xpm"))
		return (false);
	if (!get_sprite_data(g, &g->menu[3], MAIN_MENU "4.xpm"))
		return (false);
	if (!get_sprite_data(g, &g->pause, "./assets/controls_sheet.xpm"))
		return (false);
	if (!get_sprite_data(g, &g->mini.frame, "./assets/frame.xpm"))
		return (false);
	if (!get_sprite_data(g, &g->hand[0], LANTERN "off.xpm"))
		return (false);
	if (!get_sprite_data(g, &g->hand[1], LANTERN "on.xpm"))
		return (false);
	if (!get_sprite_data(g, &g->flash[0], "./assets/off.xpm"))
		return (false);
	if (!get_sprite_data(g, &g->flash[1], "./assets/on.xpm"))
		return (false);
	return (true);
}

static bool	load_walls(t_game *g)
{
	if (!get_sprite_data(g, &g->walls[0], g->paths[0]))
		return (false);
	if (!get_sprite_data(g, &g->walls[1], g->paths[1]))
		return (false);
	if (!get_sprite_data(g, &g->walls[2], g->paths[2]))
		return (false);
	if (!get_sprite_data(g, &g->walls[3], g->paths[3]))
		return (false);
	return (true);
}

/// @brief creates a new image of WIDTH and HEIGTH size and gets it's address
/// @return true on success, false on failure
static bool	get_img(t_game *game, int width, int height)
{
	game->bg.img = mlx_new_image(game->mlx, width, height);
	if (!game->bg.img)
		return (printf_fd(2, M_MLXIMGF), false);
	game->bg.addr = mlx_get_data_addr(game->bg.img, &game->bg.bpp,
			&game->bg.len, &game->bg.endian);
	if (!game->bg.addr)
		return (printf_fd(2, M_MLXADRF), false);
	return (true);
}
