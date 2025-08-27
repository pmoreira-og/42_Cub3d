#include "../../include/cub3d.h"

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
	return (printf_fd(2, "survived map\n"), true);
}

/// @brief checks if the map contains any invalid chars or repeated player positions
/// @param map the matrix with the whole map
/// @param heigth map heigth will be stored here
/// @param width max width will be stored here
/// @param player the direction of the player is stored here
/// @return true when invalid, false when valid
bool	invalid_chars(char **map, size_t *heigth, size_t *width, t_type *player)
{
	size_t	i;

	while (map[*heigth])
	{
		if (!ft_strcmp(map[*heigth], "\n"))
			return (printf_fd(2, M_ERRO M_MAPEMP), true);
		i = 0;
		while (map[*heigth][i] && map[*heigth][i] != '\n')
		{
			if (!ft_strchr("01NSEW ", map[*heigth][i]))
				return (printf_fd(2, M_ERRO M_MAPCH), true);
			if (ft_strchr("NSEW", map[*heigth][i]) && !assign_player_pos(player,
					map[*heigth][i]))
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

bool	assign_player_pos(t_type *player, char type)
{
	if (*player)
		return (false);
	if (type == 'N')
		*player = PLAYER_N;
	else if (type == 'S')
		*player = PLAYER_S;
	else if (type == 'E')
		*player = PLAYER_E;
	else if (type == 'W')
		*player = PLAYER_W;
	return (true);
}

char	**make_padded_map(t_parse *parse)
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
	// ft_printf("\nPADDED MAP:\n");
	// matrix_print(new);
	return (new);
}
