#include "../../include/cub3d.h"

bool	setup_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (merror("game.mlx"), false);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, TITLE);
	if (!game->win)
		return (merror("game.win"), false);
	if (!load_walls(game))
		return (merror("load_walls"), false);
	// ! CHANGE MESSAGE!!!!!!
	if (!get_img(game, WIDTH, HEIGHT))
		return (merror("game.bg"), false);
	game->bg.width = WIDTH;
	game->bg.height = HEIGHT;
	game->player.flash_fov = deg2rad(FLASH_FOV);
	game->player.cos_flash = cos(game->player.flash_fov / 2);
	game->player.ambient = 0.15;
	game->player.flash_k1 = 0.2;
	game->player.flash_k2 = 0.1;
	game->speed = 1;
	return (printf_fd(2, "survived mlx setup\n"), true);
}
