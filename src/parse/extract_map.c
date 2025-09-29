/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:11:28 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/09/29 18:11:29 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	invalid_chars(char **map, int *heigth, int *width, t_type *player);
static char	**make_padded_map(t_parse *parse);

/// @brief extracts and validates the map
/// @return true on success, false on failure
bool	extract_map(t_parse *parse)
{
	if (invalid_chars(parse->map_st, &parse->heigth, &parse->width,
			&parse->player))
		return (false);
	parse->padded = make_padded_map(parse);
	if (!parse->padded)
		return (printf_fd(2, M_ERRO M_MFL), false);
	if (!check_surrounding_walls(parse))
		return (printf_fd(2, M_ERRO M_WALLS), false);
	safe_close(parse->fd);
	return (true);
}

/// @brief checks if the map contains any invalid chars or
/// repeated player positions
/// @param map the matrix with the whole map
/// @param heigth map heigth will be stored here
/// @param width max width will be stored here
/// @param player the direction of the player is stored here
/// @return true when invalid, false when valid
static bool	invalid_chars(char **map, int *heigth, int *width, t_type *player)
{
	int	i;

	while (map[*heigth])
	{
		if (!ft_strcmp(map[*heigth], "\n"))
			return (printf_fd(2, M_ERRO M_MAPEMP), true);
		i = 0;
		while (map[*heigth][i] && map[*heigth][i] != '\n')
		{
			if (!ft_strchr("01NSEW ", map[*heigth][i]))
				return (printf_fd(2, M_ERRO M_MAPCH), true);
			if (ft_strchr("NSEW", map[*heigth][i])
				&& !assign_point_type(map[*heigth][i], player))
				return (printf_fd(2, M_ERRO M_PPOS), true);
			i++;
		}
		if (i > *width)
			*width = i;
		(*heigth)++;
	}
	if (!(*player))
		return (printf_fd(2, M_ERRO M_MPPOS), true);
	return (false);
}

/// @param c can be either '1', '0', 'N', 'S', 'E', 'W' or '2'
/// @param point where to store the type of the point
/// @return true if the point hasnt been assigned yet, false if its repeated
bool	assign_point_type(char c, t_type *point)
{
	if (*point)
		return (false);
	if (c == '1')
		*point = WALL;
	else if (c == '0')
		*point = FLOOR;
	else if (c == 'N')
		*point = PLAYER_N;
	else if (c == 'S')
		*point = PLAYER_S;
	else if (c == 'E')
		*point = PLAYER_E;
	else if (c == 'W')
		*point = PLAYER_W;
	else
		*point = VOID;
	return (true);
}

/// @brief makes a version of map but with a border of spaces all around
/// @return the padded map
static char	**make_padded_map(t_parse *parse)
{
	char	**new;
	int		i;

	new = (char **)matrix_allocer(sizeof(char *), sizeof(char), parse->heigth
			+ 2, parse->width + 2);
	if (!new)
		return (NULL);
	i = -1;
	while (new[++i])
		ft_memset(new[i], ' ', parse->width + 2 * sizeof(char));
	i = -1;
	while (new[++i + 2])
		ft_memcpy(&new[i + 1][1], parse->map_st[i], len_until(parse->map_st[i],
				'\n'));
	return (new);
}
