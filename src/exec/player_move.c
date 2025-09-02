#include "../../include/cub3d.h"

static int	tile_blocked(t_game *g, int tx, int ty)
{
	if (tx < 0 || ty < 0
		|| ty >= (int) g->map_height || tx >= (int) g->map_width)
		return (1);
	return (!valid_move(&g->matrix[ty][tx]));
}

/// @brief Check if a pixel square collides with the game map
/// @param g The game state
/// @param px The x position of the pixel square
/// @param py The y position of the pixel square
/// @param radius_pix The radius of the pixel square
/// @return 1 if there is a collision, 0 otherwise
static int	check_block(t_game *g, double px, double py, double radius_pix)
{
	int	tx[4];
	int	ty[4];
	// Canto superior esquerdo
	tx[0] = (int)((px - radius_pix) / g->scale);
	ty[0] = (int)((py - radius_pix) / g->scale);
	// Canto superior direito
	tx[1] = (int)((px + radius_pix) / g->scale);
	ty[1] = ty[0];
	// Canto inferior esquerdo
	tx[2] = tx[0];
	ty[2] = (int)((py + radius_pix) / g->scale);
	// Canto inferior direito
	tx[3] = tx[1];
	ty[3] = ty[2];
	return (tile_blocked(g, tx[0], ty[0])
		|| tile_blocked(g, tx[1], ty[1])
		|| tile_blocked(g, tx[2], ty[2])
		|| tile_blocked(g, tx[3], ty[3]));
}

void	move_player(t_game *g, int x_axis, double value)
{
	double	radius_pix;
	double	new_x;
	double	new_y;
	int		is_blocked;

	new_x = g->player.pos_x;
	new_y = g->player.pos_y;
	radius_pix = PLAYER_RADIUS_TILES * g->scale;
	if (x_axis)
		new_x += value;
	else
		new_y += value;
	if (x_axis)
		is_blocked = check_block(g, new_x, g->player.pos_y, radius_pix);
	else
		is_blocked = check_block(g, g->player.pos_x, new_y, radius_pix);
	if (!is_blocked)
	{
		if (x_axis)
			g->player.pos_x = new_x;
		else
			g->player.pos_y = new_y;
	}
}

void	get_moving(t_game *g, double angle)
{
	double	d[2];

	d[0] = cos(angle);
	d[1] = -sin(angle);
	move_player(g, 1, d[0] * MOVESPEED);
	move_player(g, 0, d[1] * MOVESPEED);
}

void	move_handler(t_game *g)
{
	if (g->player.rot_left && !g->player.rot_right)
		g->player.direction += deg2rad(ROTSPEED);
	if (g->player.rot_right && !g->player.rot_left)
		g->player.direction -= deg2rad(ROTSPEED);
	if (g->player.m_left && !g->player.m_right)
		get_moving(g, g->player.direction + deg2rad(90));
	if (g->player.m_right && !g->player.m_left)
		get_moving(g, g->player.direction - deg2rad(90));
	if (g->player.m_forward && !g->player.m_back)
		get_moving(g, g->player.direction);
	if (g->player.m_back && !g->player.m_forward)
		get_moving(g, g->player.direction + deg2rad(180));
	
}
