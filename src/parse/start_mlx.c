#include "../../include/cub3d.h"

bool	setup_mlx(t_game *game)
{
	(void)game;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (merror("game.mlx"), false);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, TITLE);
	if (!game->win)
		return (merror("game.win"), false);
	game->bg = get_img(game);
	if (!game->bg)
		return (merror("game.bg.img"), false);
	return (printf_fd(2, "survived mlx setup\n"), true);
}
