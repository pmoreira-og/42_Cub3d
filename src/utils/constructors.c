#include "../../include/cub3d.h"

bool	get_img(t_game *game, int width, int height)
{
	game->bg.img = mlx_new_image(game->mlx, width, height);
	if (!game->bg.img)
		return (printf_fd(2, "mlx img error\n"), false);
	game->bg.addr = mlx_get_data_addr(game->bg.img, &game->bg.bpp,
			&game->bg.len, &game->bg.endian);
	if (!game->bg.addr)
		return (printf_fd(2, "mlx img addr error\n"), false);
	return (true);
}
