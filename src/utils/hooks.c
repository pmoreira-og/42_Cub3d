#include "../../include/cub3d.h"

void	manager(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_win_mouse, game);
	mlx_hook(game->win, 2, 1L << 0, key_press_manager, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_manager, game);
}

int	close_win_mouse(t_game *data)
{
	armageddon(data);
	exit(0);
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
		mlx_put_image_to_window(data->mlx, data->win, data->bg.img, 0, 0);
	}
	return (0);
}

int	key_release_manager(int keycode, t_game *g)
{
	if (g->scene == MENU)
		return (0);
	if (keycode == ESC)
		close_win_mouse(g);
	if (keycode == SHIFT)
		g->sprint = false;
	if (keycode == KEY_W && g->player.m_forward)
		g->player.m_forward = 0;
	if (keycode == KEY_S && g->player.m_back)
		g->player.m_back = 0;
	if (keycode == KEY_A && g->player.m_left)
		g->player.m_left = 0;
	if (keycode == KEY_D && g->player.m_right)
		g->player.m_right = 0;
	if (keycode == VK_LEFT && g->player.rot_left)
		g->player.rot_left = 0;
	if (keycode == VK_RIGHT && g->player.rot_right)
		g->player.rot_right = 0;
	if (keycode == SPACE)
		g->player.vertical_view -= HEIGHT / 10;
	if (keycode == 'f')
		g->player.flash_on = !g->player.flash_on;
	if (keycode == 'm')
		g->mini.show = !g->mini.show;
	if (g->mini.show && keycode == 'k' && g->mini.scale == 1)
		g->mini.scale = 3;
	else if (g->mini.show && keycode == 'k')
		g->mini.scale = 1;
	return (0);
}
