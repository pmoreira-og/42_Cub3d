#include "../../include/cub3d.h"

int	close_win_mouse(t_game *data)
{
	armageddon(data);
	exit (0);
}

int	key_press_manager(int keycode, t_game *data)
{
	if (keycode == ESC)
		close_win_mouse(data);
	if (keycode == VK_LEFT)
		data->player.rotate = 1;
	if (keycode == VK_RIGHT)
		data->player.rotate = -1;
	if (keycode == KEY_W)
		data->player.move_y = 1;
	if (keycode == KEY_S)
		data->player.move_y = -1;
	if (keycode == KEY_A)
		data->player.move_x = -1;
	if (keycode == KEY_D)
		data->player.move_x = 1;
	return (0);
}

int	key_release_manager(int keycode, t_game *data)
{
	if (keycode == ESC)
		close_win_mouse(data);
	if (keycode == KEY_W && data->player.move_y == 1)
		data->player.move_y = 0;
	if (keycode == KEY_S && data->player.move_y == -1)
		data->player.move_y = 0;
	if (keycode == KEY_A && data->player.move_x == -1)
		data->player.move_x += 1;
	if (keycode == KEY_D && data->player.move_x == 1)
		data->player.move_x -= 1;
	if (keycode == VK_LEFT && data->player.rotate <= 1)
		data->player.rotate = 0;
	if (keycode == VK_RIGHT && data->player.rotate >= -1)
		data->player.rotate = 0;
	return (0);
}
