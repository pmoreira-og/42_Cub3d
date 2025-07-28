#include "../include/cub3d.h"

void	manager(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_win_mouse, game);
	mlx_hook(game->win, 2, 1L << 0, close_win_keycode, game);
}

bool	render_map(t_game *game)
{
	// size_t	x;
	// size_t	y;

	// y = 0;
	// while(y < game->map_height)
	// {
	// 	x = 0;
	// 	while (x < game->map_width)
	// 	{
	// 		if (j != (data->table->cols - 1))
	// 			handle_line(data->fdf, &data->fdf->map->pts[i][j],
	// 				&data->fdf->map->pts[i][j + 1]);
	// 		if (i != (data->table->lines - 1))
	// 			handle_line(data->fdf, &data->fdf->map->pts[i][j],
	// 				&data->fdf->map->pts[i + 1][j]);
	// 		if (x + 1 < game->map_width)
	// 			draw_line(game->bg, game->matrix[y][x],
	// 				game->matrix[y][x+1], 0xFFFFFF);
	// 		x++;
	// 	}
	// 	y++;
	// }
	t_point a,b;
	t_point	*hit;
	ft_bzero(&a, sizeof(t_point));
	a.y = 0;
	a.x = WIDTH;
	b.x = 0;
	b.y = HEIGHT;
	draw_line(game->bg, a, b, 0xFF350C);
	if (collider(a, b, game, &hit))
		printf("bateu\n");
	mlx_put_image_to_window(game->mlx, game->win, game->bg->img, 0, 0);
	return (1);
}

char	**copy_map(char **map)
{
	char	**new_map;
	int		i;
	int		j;

	i = -1;
	while (map && map[++i]);
	new_map = ft_calloc(i + 1, sizeof(char *));
	if (!new_map)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_map[j] = ft_strdup(map[j]);
		j++;
	}
	return (new_map);
}

int	main(int ac, char **av)
{
	t_game	game;
	char *map[] = {
		"111111",
		"100101    1",
		"101001   101",
		"1100N1    1",
		"111111111",
		NULL
	};

	if (ac > 2)
		return (0);
	init_data(&game, map);
	if (ac == 2 && !ft_strcmp("-d", av[1]))
		game.debug = true;
	if(game.debug)
	{
		print_matrix(&game);
		print_map(&game);
	}
	render_map(&game);
	manager(&game);
	mlx_loop(game.mlx);
	return (0);
}
