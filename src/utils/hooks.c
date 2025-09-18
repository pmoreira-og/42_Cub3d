#include "../../include/cub3d.h"

void	manager(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_win_mouse, game);
	mlx_hook(game->win, 2, 1L << 0, key_press_manager, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_manager, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_handler, game);
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
		data->player.act.rot_left = false;
		data->player.act.rot_right = false;
		mlx_put_image_to_window(data->mlx, data->win, data->bg.img, 0, 0);
	}
	return (0);
}

void	handle_game_hooks(int keycode, t_game *g)
{
	if (keycode == BACKSPACE)
		g->scene = MENU;
	if (keycode == SHIFT && !g->player.act.sneaking)
		g->player.act.sprint = true;
	if (keycode == VK_LEFT)
		g->player.act.rot_left = true;
	if (keycode == VK_RIGHT)
		g->player.act.rot_right = true;
	if (keycode == KEY_W)
		g->player.act.m_forward = true;
	if (keycode == KEY_S)
		g->player.act.m_back = true;
	if (keycode == KEY_A)
		g->player.act.m_left = true;
	if (keycode == KEY_D)
		g->player.act.m_right = true;
	if (keycode == VK_CTRL && !g->player.act.sprint)
	{
		g->player.vertical_view -= HEIGHT / 10;
		g->player.act.sneaking = true;
	}
	if (keycode == VK_DOWN && (-g->player.vertical_view < (int)(HEIGHT / 5)))
		g->player.vertical_view -= 10;
	if (keycode == VK_UP && g->player.vertical_view < (int)(HEIGHT / 5))
		g->player.vertical_view += 10;
}

int	key_release_manager(int keycode, t_game *g)
{
	if (g->scene == MENU)
		return (0);
	if (keycode == ESC)
		close_win_mouse(g);
	if (keycode == SHIFT && g->player.act.sprint)
		g->player.act.sprint = false;
	if (keycode == KEY_W && g->player.act.m_forward)
		g->player.act.m_forward = false;
	if (keycode == KEY_S && g->player.act.m_back)
		g->player.act.m_back = false;
	if (keycode == KEY_A && g->player.act.m_left)
		g->player.act.m_left = false;
	if (keycode == KEY_D && g->player.act.m_right)
		g->player.act.m_right = false;
	if (keycode == VK_LEFT && g->player.act.rot_left)
		g->player.act.rot_left = false;
	if (keycode == VK_RIGHT && g->player.act.rot_right)
		g->player.act.rot_right = false;
	if (keycode == VK_CTRL && g->player.act.sneaking)
	{
		g->player.vertical_view += HEIGHT / 10;
		g->player.act.sneaking = false;
	}
	overlay_hooks(keycode, g);
	return (0);
}

void	overlay_hooks(int keycode, t_game *g)
{
	if (keycode == 'f' && time_passed(400))
		g->player.flash_on = !g->player.flash_on;
	if (keycode == 'm' && time_passed(400))
		g->mini.show = !g->mini.show;
	if (g->mini.show && keycode == 'k' && g->mini.scale == 1 \
&& time_passed(100))
		g->mini.scale = 3;
	else if (g->mini.show && keycode == 'k' && time_passed(300))
		g->mini.scale = 1;
}
