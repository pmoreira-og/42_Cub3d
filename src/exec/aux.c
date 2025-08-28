#include "../../include/cub3d.h"
void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	get_scale(t_game *game)
{
	game->scale = ft_min((WIDTH / game->map_width),
			(HEIGHT / game->map_height));
}

double	deg2rad(double angle)
{
	return (angle * (PI/180));
}

void	set_player_dir(t_game *game, t_point *src)
{
	game->player.pos_x = src->x * (game->scale);
	game->player.pos_y = src->y * (game->scale);
	game->player.pos_x += (game->scale / 2);
	game->player.pos_y += (game->scale / 2);

	if (src->type == PLAYER_E)
		game->player.direction = deg2rad(0);
	if (src->type == PLAYER_W)
		game->player.direction = deg2rad(180);
	if (src->type == PLAYER_S)
		game->player.direction = deg2rad(270);
	if (src->type == PLAYER_N)
		game->player.direction = deg2rad(90);
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
