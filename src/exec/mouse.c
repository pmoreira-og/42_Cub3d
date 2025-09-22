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
	static bool	ignore_frame;
	int			dx;
	double		sensitivity;

	(void) y;
	if (g->scene != GAME)
		return (1);
	if (ignore_frame)
	{
		ignore_frame = false;
		return (0);
	}
	dx = x - (WIDTH / 2);
	sensitivity = 0.001;
	if (dx != 0)
	{
		g->player.direction -= dx * sensitivity;
		ignore_frame = true;
		hold_mouse(g);
	}
	return (0);
}
