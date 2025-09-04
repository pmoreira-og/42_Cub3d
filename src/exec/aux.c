#include "../../include/cub3d.h"

void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

double	deg2rad(double angle)
{
	return (angle * (PI / 180));
}

void	set_player_dir(t_game *game, t_point *src)
{
	game->player.pos_x = src->x + 0.5;
	game->player.pos_y = src->y + 0.5;
	game->player.plane_mag = tan(deg2rad((double) FOV) / 2.0);
	if (src->type == PLAYER_E)
		game->player.direction = deg2rad(0);
	if (src->type == PLAYER_W)
		game->player.direction = deg2rad(180);
	if (src->type == PLAYER_S)
		game->player.direction = deg2rad(270);
	if (src->type == PLAYER_N)
		game->player.direction = deg2rad(90);
	init_minimap(game);
	init_bob_struct(game);
}

double	normalize_rad(double rad)
{
	double	inc;

	if (rad < 0)
		inc = 2 * PI;
	else
		inc = -2 * PI;
	while (rad >= 2 * PI || rad < 0)
		rad += inc;
	return (rad);
}
