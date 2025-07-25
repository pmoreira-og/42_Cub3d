#include "../../include/cub3d.h"

int	close_win_keycode(int keycode, t_game *data)
{
	if (keycode == ESC)
	{
		armageddon(data);
		exit (0);
	}
	return (0);
}

int	close_win_mouse(t_game *data)
{
	armageddon(data);
	exit (0);
}