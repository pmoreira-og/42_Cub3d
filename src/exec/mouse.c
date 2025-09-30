/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:26:20 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/09/30 10:17:57 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	close_win_mouse(t_game *data)
{
	cleanup_all(data);
	exit(0);
}

void	hide_mouse(t_game *g)
{
	if (g->scene == GAME)
	{
		if (HIDE)
			mlx_mouse_hide(g->mlx, g->win);
	}
	else
	{
		if (HIDE)
			mlx_mouse_show(g->mlx, g->win);
	}
	if (g->counter == 42)
		g->fun = true;
}

/// @brief Safeguard function to y axis toggle with mouse.
/// @param value player vertical view var
/// @param dy mouse movement
static bool	check_valid_vertical(int value, int dy, t_game *g)
{
	if (g->fun)
		return (true);
	if (dy < 0 && value < (int)(HEIGHT / 5))
		return (true);
	if (dy > 0 && (-value < (int)(HEIGHT / 5)))
		return (true);
	return (false);
}

int	mouse_handler(int x, int y, t_game *g)
{
	static bool	ignore_frame;
	int			dx;
	int			dy;

	if (g->scene != GAME)
		return (1);
	if (ignore_frame)
	{
		ignore_frame = false;
		return (0);
	}
	dx = x - (WIDTH / 2);
	dy = y - (HEIGHT / 2);
	if (dx != 0 || dy != 0)
	{
		g->player.direction -= dx * 0.001;
		if (check_valid_vertical(g->player.vertical_view, dy, g))
			g->player.vertical_view -= dy;
		ignore_frame = true;
		mlx_mouse_move(g->mlx, g->win, WIDTH / 2, HEIGHT / 2);
	}
	return (0);
}
