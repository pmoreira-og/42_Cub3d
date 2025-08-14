#include "../../include/cub3d.h"

t_type	get_player_dir(int c)
{
	if (!c)
		return (VOID);
	if (ft_strchr("E", c))
		return (PLAYER_E);
	if (ft_strchr("W", c))
		return (PLAYER_W);
	if (ft_strchr("S", c))
		return (PLAYER_S);
	if (ft_strchr("N", c))
		return (PLAYER_N);
	return (VOID);
}

bool	valid_move(t_point *check)
{
	if (is_player(check))
		return (true);
	if (check->type == FLOOR)
		return (true);
	return (false);
}

/// @brief Prints malloc error message on stderr.
/// @param msg Message for malloc debug porposes.
void	merror(char *msg)
{
	if (msg)
		printf_fd(2, "Malloc:%s\n", msg);
}

bool	get_next_img(t_game *game)
{
	if (game->bg->img)
	{
		mlx_destroy_image(game->mlx, game->bg->img);
		free(game->bg);
		game->bg = NULL;
	}
	game->bg = get_img(game);
	if (!game->bg)
		return (merror("get_next_img"), false);
	return (true);
}

bool	is_moved(t_game *g)
{
	static	double	x;
	static	double	y;
	static	double	dir;

	if (x != g->player.pos_x || y != g->player.pos_y
		|| dir != g->player.direction)
	{
		x = g->player.pos_x;
		y = g->player.pos_y;
		dir = g->player.direction;
		return (true);
	}
	return (false);
}
