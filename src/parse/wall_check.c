/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:11:41 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/09/29 18:11:42 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	space_flood_fill(int y, int x, t_parse *parse);

/// @brief finds spaces and replaces them with '2' to check
/// if any floor or player isn't surrounded by '1's 
/// @return true on success, false on failure
bool	check_surrounding_walls(t_parse *parse)
{
	int	errors;
	int	y;
	int	x;

	errors = 0;
	y = -1;
	while (parse->padded[++y] && !errors)
	{
		x = -1;
		while (parse->padded[y][++x] && !errors)
			if (parse->padded[y][x] == ' ')
				errors = space_flood_fill(y, x, parse);
	}
	if (errors)
		return (false);
	return (true);
}

/// @brief flood fill on spaces to check for walls
/// @return amount of errors (exposed floor or player) 
static int	space_flood_fill(int y, int x, t_parse *parse)
{
	int	errors;

	if (y < 0 || y > (int)parse->heigth + 1 || x < 0 || x > (int)parse->width
		+ 1 || ft_strchr("12", parse->padded[y][x]))
		return (0);
	if (ft_strchr("0NSEW", parse->padded[y][x]))
		return (1);
	errors = 0;
	if (parse->padded[y][x] == ' ')
		parse->padded[y][x] = '2';
	errors += space_flood_fill(y + 1, x, parse);
	errors += space_flood_fill(y - 1, x, parse);
	errors += space_flood_fill(y, x - 1, parse);
	errors += space_flood_fill(y, x + 1, parse);
	return (errors);
}
