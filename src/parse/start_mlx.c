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
	if (!get_img(game, WIDTH, HEIGHT))
		return (merror("game.bg"), false);

	return (printf_fd(2, "survived mlx setup\n"), true);
}
