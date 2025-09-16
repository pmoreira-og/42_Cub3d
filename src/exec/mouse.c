#include "../../include/cub3d.h"

int	close_win_mouse(t_game *data)
{
	armageddon(data);
	exit(0);
}

static void	hold_mouse(t_game *g)
{
	if (g->scene == GAME)
	{
		if (HIDE)
			mlx_mouse_hide(g->mlx, g->win);
		mlx_mouse_move(g->mlx, g->win, WIDTH / 2, HEIGHT / 2);
	}
	else
	{
		if (HIDE)
			mlx_mouse_show(g->mlx, g->win);
	}
}

int	mouse_handler(int x, int y, t_game *g)
{
	static int	prev_x;

	(void) y;
	if (prev_x == x)
	{
		g->player.rot_right = false;
		g->player.rot_left = false;
		return (0);
	}
	hold_mouse(g);
	if (prev_x < x)
		g->player.rot_right = true;
	if (prev_x > x)
		g->player.rot_left = true;
	prev_x = x;
	return (0);
}
