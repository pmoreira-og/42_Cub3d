#include "../../include/cub3d.h"

int	close_win_mouse(t_game *data)
{
	armageddon(data);
	exit (0);
}

void	move_player(t_game *data, int x_axis, double value)
{
	int	pos_x;
	int	pos_y;
	int	inc;

	pos_x = (int) data->player.pos_x;
	pos_y = (int) data->player.pos_y;
	if (value < 0)
		inc = -1;
	else
		inc = 1;
	if (x_axis)
	{
		if (valid_move(&data->matrix[pos_y][pos_x + inc]))
			data->player.pos_x += value;
	}
	else
	{
		if (valid_move(&data->matrix[pos_y + inc][pos_x]))
			data->player.pos_y += value;
	}
	printf("player at %s\n", get_type(data->matrix[ (int) data->player.pos_y][(int)data->player.pos_x].type));
}

int	key_manager(int keycode, t_game *data)
{
	if (keycode == ESC)
		close_win_mouse(data);
	if (keycode == VK_LEFT)
		data->player.direction += 0.5;
	if (keycode == VK_RIGHT)
		data->player.direction -= 0.5;
	if (keycode == KEY_W)
		move_player(data, 0, -0.01);
		// data->player.pos_y -= 0.01;
	if (keycode == KEY_S)
		move_player(data, 0, 0.01);
		// data->player.pos_y += 0.01;
	if (keycode == KEY_A)
		move_player(data, 1, -0.01);
		// data->player.pos_x -= 0.01;
	if (keycode == KEY_D)
		move_player(data, 1, 0.01);
		// data->player.pos_x += 0.01;
	return (0);
}
