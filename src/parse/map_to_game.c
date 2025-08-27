#include "../../include/cub3d.h"

bool	map_to_game(t_parse *parse, t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	get_exact_hei_wid(parse);
	game->matrix = make_point_map(parse);
	if (!game->matrix)
		return (printf_fd(2, M_ERRO M_MFL), false);
	pass_info_to_map(parse, game);
	// print_map(game);
	return (printf_fd(2, "survived map to game\n"), true);
}

void	get_exact_hei_wid(t_parse *parse)
{
	int	i;
	int	margin;

	i = 1;
	while (!ft_strchr(parse->padded[i], '1'))
		i++;
	parse->map_st = &parse->padded[i];
	i = parse->heigth - i - 1;
	while (!ft_strchr(parse->map_st[i], '1'))
		i--;
	parse->heigth = i + 1;
	// printf("exact map heigth: %ld\n", parse->heigth);
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
	// printf("exact map width: %ld\n", parse->width);
	// printf("margin_l: %d\n", parse->margin_l);
	// printf("margin_r: %d\n", parse->margin_r);
}

t_point	**make_point_map(t_parse *parse)
{
	t_point	**new;
	size_t	y;
	size_t	x;

	new = (t_point **)matrix_allocer(sizeof(t_point *), sizeof(t_point),
			parse->heigth, parse->width);
	if (!new)
		return (NULL);
	y = 0;
	while (y < parse->heigth)
	{
		x = 0;
		while (x < parse->width)
		{
			new[y][x].x = x;
			new[y][x].y = y;
			new[y][x].type = get_point_type(parse->map_st[y][x + parse->margin_l
					+ 1]);
			x++;
		}
		y++;
	}
	return (new);
}

t_type	get_point_type(int c)
{
	if (c == '1')
		return (WALL);
	else if (c == '0')
		return (FLOOR);
	else if (c == 'N')
		return (PLAYER_N);
	else if (c == 'S')
		return (PLAYER_S);
	else if (c == 'E')
		return (PLAYER_E);
	else if (c == 'W')
		return (PLAYER_W);
	return (VOID);
}

void	pass_info_to_map(t_parse *parse, t_game *game)
{
	t_point	a;

	game->floor_color = parse->hd.floor;
	game->ceiling_color = parse->hd.ceiling;
	game->map_height = parse->heigth;
	game->map_width = parse->width;
	get_scale(game);
	find_player(game, &a);
	set_player_dir(game, &a);
}
