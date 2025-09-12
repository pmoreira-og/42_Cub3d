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
	info_to_game(parse, game);
	// print_map(game);
	return (printf_fd(2, "survived map to game\n"), true);
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
	// printf("exact map heigth: %ld\n", parse->heigth);
	// printf("exact map width: %ld\n", parse->width);
	// printf("margin_l: %d\n", parse->margin_l);
	// printf("margin_r: %d\n", parse->margin_r);
}

/// @brief convertes the char **map to a t_point **map
/// @return a map with cordinates and element types
t_point	**make_point_map(t_parse *parse)
{
	t_point	**new;
	int	y;
	int	x;

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
			new[y][x].type = assign_point_type(parse->map_st[y][x
					+ parse->margin_l + 1]);
		}
	}
	return (new);
}

/// @brief passes textures, colors, measures and player info from PARSE to GAME
void	info_to_game(t_parse *parse, t_game *game)
{
	t_point	player;

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
	find_player(game, &player);
	set_player_dir(game, &player);
}

/// @brief initialized all windows and images needed for rendering
/// @param game struct that will be used to run the game
/// @return true on success, false on failure
bool	setup_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (merror("game.mlx"), false);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, TITLE);
	if (!game->win)
		return (merror("game.win"), false);
	if (!load_walls(game))
		return (printf_fd(2, M_ERRO M_INVXPM), false);
	if (!get_img(game, WIDTH, HEIGHT))
		return (merror("game.bg"), false);
	game->bg.width = WIDTH;
	game->bg.height = HEIGHT;
	game->player.flash_fov = deg2rad(FLASH_FOV);
	game->player.cos_flash = cos(game->player.flash_fov / 2);
	game->player.ambient = 0.05;
	game->player.flash_k1 = 0.2;
	game->player.flash_k2 = 0.1;
	game->sprint = false;
	return (printf_fd(2, "survived mlx setup\n"), true);
}
