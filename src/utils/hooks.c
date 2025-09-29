/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:15:01 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/09/29 18:21:46 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	handle_game_hooks(int keycode, t_game *g);
static void	handle_menu_hooks(int keycode, int *prev, t_game *g);
static void	overlay_hooks(int keycode, t_game *g);

int	key_press_manager(int keycode, t_game *data)
{
	static int	prev;

	if (keycode == ESC)
		close_win_mouse(data);
	if (data->scene == GAME)
	{
		if (keycode == BACKSPACE)
		{
			prev = data->scene;
			data->scene = PAUSE;
			mlx_put_image_to_window(data->mlx, data->win, data->pause.img, 0,
				0);
			return (0);
		}
		handle_game_hooks(keycode, data);
	}
	else
		handle_menu_hooks(keycode, &prev, data);
	return (0);
}

static void	handle_game_hooks(int keycode, t_game *g)
{
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

static void	handle_menu_hooks(int keycode, int *prev, t_game *g)
{
	if (g->scene == MENU)
	{
		if (keycode == ENTER)
			g->scene = GAME;
		else if (keycode == BACKSPACE)
		{
			*prev = g->scene;
			g->scene = PAUSE;
			mlx_put_image_to_window(g->mlx, g->win, g->pause.img, 0, 0);
		}
	}
	else if (g->scene == PAUSE && keycode == BACKSPACE)
	{
		g->scene = *prev;
		if (*prev == GAME)
		{
			ft_bzero(&g->player.act, sizeof(t_action));
			mlx_put_image_to_window(g->mlx, g->win, g->bg.img, 0, 0);
		}
	}
}

int	key_release_manager(int keycode, t_game *g)
{
	if (g->scene == MENU || g->scene == PAUSE)
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

static void	overlay_hooks(int keycode, t_game *g)
{
	if (keycode == 'f' && time_passed(400))
		g->player.flash_on = !g->player.flash_on;
	else if (keycode == 'h' && time_passed(400))
		g->mini.show = !g->mini.show;
	else if (g->mini.show && keycode == 'm' && g->mini.scale == 1
		&& time_passed(100))
		g->mini.scale = 3;
	else if (g->mini.show && keycode == 'm' && time_passed(300))
		g->mini.scale = 1;
}
