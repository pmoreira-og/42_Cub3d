#include "../../include/cub3d.h"

/// @brief passes the all needed elements from PARSE to GAME
/// @param parse struct with everything obtained in the parsing
/// @param game struct that will be used to run the game
/// @return true on success, false on failure
bool	map_to_game(t_parse *parse, t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	get_exact_hei_wid(parse);
	game->matrix = make_point_map(parse);
	if (!game->matrix)
		return (printf_fd(2, M_ERRO M_MFL), false);
	game->paths[0] = parse->hd.no;
	parse->hd.no = NULL;
	game->paths[1] = parse->hd.ea;
	parse->hd.ea = NULL;
	game->paths[2] = parse->hd.so;
	parse->hd.so = NULL;
	game->paths[3] = parse->hd.we;
	parse->hd.we = NULL;
	game->floor_color = parse->hd.floor;
	game->ceiling_color = parse->hd.ceiling;
	game->map_height = parse->heigth;
	game->map_width = parse->width;
	init_player(game);
	init_minimap(game);
	return (true);
}

/// @brief cuts empty spaces from the heigth and width of the map
void	get_exact_hei_wid(t_parse *parse)
{
	int	i;
	int	margin;

	i = 1;
	while (!ft_strchr(parse->padded[i], '1'))
		i++;
	parse->map_st = &parse->padded[i];
	i = parse->heigth - i;
	while (!ft_strchr(parse->map_st[i], '1'))
		i--;
	parse->heigth = i + 1;
	i = -1;
	while (++i < (int)parse->heigth)
	{
		margin = len_until(&parse->map_st[i][1], '1');
		if (margin < parse->margin_l || parse->margin_l == -1)
			parse->margin_l = margin;
		margin = parse->width - (ft_strrchr(&parse->map_st[i][1 + margin], '1')
				- parse->map_st[i]);
		if (margin < parse->margin_r || parse->margin_r == -1)
			parse->margin_r = margin;
	}
	parse->width = parse->width - parse->margin_l - parse->margin_r;
}

/// @brief convertes the char **map to a t_point **map
/// @return a map with cordinates and element types
t_point	**make_point_map(t_parse *parse)
{
	t_point	**new;
	int		y;
	int		x;

	new = (t_point **)matrix_allocer(sizeof(t_point *), sizeof(t_point),
			parse->heigth, parse->width);
	if (!new)
		return (NULL);
	y = -1;
	while (++y < parse->heigth)
	{
		x = -1;
		while (++x < parse->width)
		{
			new[y][x].x = x;
			new[y][x].y = y;
			assign_point_type(parse->map_st[y][x + parse->margin_l + 1],
				&new[y][x].type);
		}
	}
	return (new);
}

void	init_player(t_game *game)
{
	t_point	play;

	find_player(game, &play);
	game->player.pos_x = play.x + 0.5;
	game->player.pos_y = play.y + 0.5;
	game->player.plane_mag = tan(deg2rad((double)FOV) / 2.0);
	if (play.type == PLAYER_N)
		game->player.direction = deg2rad(90);
	else if (play.type == PLAYER_S)
		game->player.direction = deg2rad(270);
	else if (play.type == PLAYER_E)
		game->player.direction = deg2rad(0);
	else if (play.type == PLAYER_W)
		game->player.direction = deg2rad(180);
	game->player.flash_on = true;
	init_bob_struct(game);
}

void	find_player(t_game *game, t_point *save)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			if (game->matrix[y][x].type >= PLAYER_N
				&& game->matrix[y][x].type <= PLAYER_W)
			{
				*save = game->matrix[y][x];
				return ;
			}
		}
	}
}
