#include "../include/cub3d.h"

void	manager(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_win_mouse, game);
	mlx_hook(game->win, 2, 1L << 0, close_win_keycode, game);
}

bool	render_map(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while(y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			put_pixel(game->bg, (int) x, (int) y, 0xFFFFFF);
			x++;
		}
		y++;
	}
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

int	main(void)
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
	init_data(&game, map);
	print_game_data(&game);
	render_map(&game);
	manager(&game);
	mlx_loop(game.mlx);
	printf("Hello World\n");
	return (0);
}