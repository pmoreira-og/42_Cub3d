#include "../include/cub3d.h"

void	manager(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_win_mouse, game);
	mlx_hook(game->win, 2, 1L << 0, key_manager, game);
}

int	render_map(t_game *game)
{
	t_point	a;

	a.x = game->player.pos_x;
	a.y = game->player.pos_y;
	// a.x += game->scale / 2;
	// a.y += game->scale / 2;
	double angle = game->player.direction - 45;
	double dist = 0;
	t_point	hit;
	while (angle <= game->player.direction + 45)
	{
		dist = collider_dda(a, angle, game, &hit);
		if (dist != -1)
			draw(a, angle, WIDTH, game);
		else
			printf("Sem colisão\n");
		angle++;
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

int	main(int ac, char **av)
{
	t_game	game;
	char *map[] = {
		"111111",
		"100101    1",
		"101001   101",
		"110S01    1",
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
	manager(&game);
	mlx_loop_hook(game.mlx, render_map, &game);
	mlx_loop(game.mlx);
	return (0);
}
