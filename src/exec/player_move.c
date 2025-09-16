#include "../../include/cub3d.h"

static int	tile_blocked(t_game *g, int tx, int ty)
{
	if (tx < 0 || ty < 0 || ty >= g->map_height || tx >= g->map_width)
		return (1);
	return (!valid_move(&g->matrix[ty][tx]));
}

/// @brief Check if a pixel square collides with the game map 0(TOP LEFT)
/// 1 (TOP RIGHT) 2 (BOTTOM LEFT) 3 (BOTTOM RIGHT).
/// @param g The game state
/// @param p The cordinates of the player
/// @param radius_pix The radius of the pixel square
/// @return 1 if there is a collision, 0 otherwise
static int	check_block(t_game *g, t_cord p, double radius_pix)
{
	int	tx[4];
	int	ty[4];

	tx[0] = (int)((p.x - radius_pix));
	ty[0] = (int)((p.y - radius_pix));
	tx[1] = (int)((p.x + radius_pix));
	ty[1] = ty[0];
	tx[2] = tx[0];
	ty[2] = (int)((p.y + radius_pix));
	tx[3] = tx[1];
	ty[3] = ty[2];
	return (tile_blocked(g, tx[0], ty[0]) || tile_blocked(g, tx[1], ty[1])
		|| tile_blocked(g, tx[2], ty[2]) || tile_blocked(g, tx[3], ty[3]));
}

static void	move_player(t_game *g, int x_axis, double value)
{
	double	radius_pix;
	t_cord	new;
	int		is_blocked;

	new = g->player.pos;
	radius_pix = PLAYER_RADIUS_TILES;
	if (x_axis)
		new.x += value;
	else
		new.y += value;
	is_blocked = check_block(g, new, radius_pix);
	if (!is_blocked)
		g->player.pos = new;
}

static void	get_moving(t_game *g, double angle)
{
	double	d[2];
	double	new_speed;

	d[0] = cos(angle);
	d[1] = -sin(angle);
	if (g->sprint && g->player.m_forward)
		new_speed = g->move_speed * 2;
	else
		new_speed = g->move_speed;
	if ((g->player.m_forward || g->player.m_back) && (g->player.m_left
			|| g->player.m_right))
		new_speed *= 0.75;
	move_player(g, 1, d[0] * new_speed);
	move_player(g, 0, d[1] * new_speed);
}

void	move_handler(t_game *g)
{
	if (g->player.rot_left && !g->player.rot_right)
		g->player.direction += deg2rad(g->rot_speed);
	if (g->player.rot_right && !g->player.rot_left)
		g->player.direction -= deg2rad(g->rot_speed);
	if (g->player.m_left && !g->player.m_right)
		get_moving(g, g->player.direction + deg2rad(90));
	if (g->player.m_right && !g->player.m_left)
		get_moving(g, g->player.direction - deg2rad(90));
	if (g->player.m_forward && !g->player.m_back)
		get_moving(g, g->player.direction);
	if (g->player.m_back && !g->player.m_forward)
		get_moving(g, g->player.direction + deg2rad(180));
}
