#include "../../include/cub3d.h"

void	manager(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_win_mouse, game);
	mlx_hook(game->win, 2, 1L << 0, key_press_manager, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_manager, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_handler, game);
}

int	close_win_mouse(t_game *data)
{
	armageddon(data);
	exit (0);
}

int	key_press_manager(int keycode, t_game *data)
{
	if (keycode == ESC)
		close_win_mouse(data);
	if (data->scene == GAME)
		handle_game_hooks(keycode, data);
	else if (data->scene == MENU && keycode == ENTER)
	{
		data->scene = GAME;
		data->player.rot_left = 0;
		data->player.rot_right = 0;
		mlx_put_image_to_window(data->mlx, data->win, data->bg.img, 0, 0);
	}
	return (0);
}

int	key_release_manager(int keycode, t_game *data)
{
	if (keycode == ESC)
		close_win_mouse(data);
	if (keycode == SHIFT)
		data->sprint = false;
	if (keycode == KEY_W && data->player.m_forward)
		data->player.m_forward = 0;
	if (keycode == KEY_S && data->player.m_back)
		data->player.m_back = 0;
	if (keycode == KEY_A && data->player.m_left)
		data->player.m_left = 0;
	if (keycode == KEY_D && data->player.m_right)
		data->player.m_right = 0;
	if (keycode == VK_LEFT && data->player.rot_left)
		data->player.rot_left = 0;
	if (keycode == VK_RIGHT && data->player.rot_right)
		data->player.rot_right = 0;
	if (keycode == SPACE)
		data->player.vertical_view -= HEIGHT / 10;
	return (0);
}
