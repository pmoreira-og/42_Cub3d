#include "../../include/cub3d.h"

/// @param c can be either '1', '0', 'N', 'S', 'E', 'W' or '2'
/// @return the t_type corresponding to C
t_type	assign_point_type(int c)
{
	if (c == '1')
		return (WALL);
	else if (c == '0')
		return (FLOOR);
	else if (c == 'N')
		return (PLAYER_N);
	else if (c == 'S')
		return (PLAYER_S);
	else if (c == 'E')
		return (PLAYER_E);
	else if (c == 'W')
		return (PLAYER_W);
	else
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
		printf_fd(2, "Malloc: %s\n", msg);
}

bool	has_moved(t_game *g)
{
	static double	x;
	static double	y;
	static double	dir;
	static int		vertical;

	if (x != g->player.pos_x || y != g->player.pos_y \
|| dir != g->player.direction || vertical != g->player.vertical_view)
	{
		x = g->player.pos_x;
		y = g->player.pos_y;
		dir = g->player.direction;
		vertical = g->player.vertical_view;
		return (true);
	}
	return (false);
}

double	get_perp_dist(double hyp, double angle, double p_angle)
{
	return (hyp * cos(angle - p_angle));
}
