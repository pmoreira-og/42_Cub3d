/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:14:12 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/09/29 18:14:13 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	valid_move(t_point *check)
{
	if (!check)
		return (false);
	if (check->type >= FLOOR && check->type <= PLAYER_W)
		return (true);
	else
		return (false);
}

bool	has_moved(t_game *g)
{
	static double	x;
	static double	y;
	static double	dir;
	static int		vertical;

	if (x != g->player.pos.x || y != g->player.pos.y
		|| dir != g->player.direction || vertical != g->player.vertical_view)
	{
		x = g->player.pos.x;
		y = g->player.pos.y;
		dir = g->player.direction;
		vertical = g->player.vertical_view;
		return (true);
	}
	return (false);
}

bool	has_changed(t_game *g)
{
	static bool	light;
	static bool	minimap;
	static int	minimap_scale;

	if (light != g->player.flash_on || minimap != g->mini.show
		|| minimap_scale != g->mini.scale)
	{
		light = g->player.flash_on;
		minimap = g->mini.show;
		minimap_scale = g->mini.scale;
		return (true);
	}
	return (false);
}
