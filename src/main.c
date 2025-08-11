#include "../include/cub3d.h"

void	manager(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_win_mouse, game);
	mlx_hook(game->win, 2, 1L << 0, close_win_keycode, game);
}

bool	render_map(t_game *game)
{
	t_point a;

	find_player(game, &a);
	a.x *= game->scale;
	a.y *= game->scale;
	a.x += game->scale / 2;
	a.y += game->scale / 2;
    printf("Player em: %d, %d\n", a.x, a.y);
	double angle = 30;
	double dist = 0;
	t_point	hit;
	while (angle <= 270)
	{
		dist = collider_dda(a, angle, game, &hit);
		// dist = collider_angle(a, angle, WIDTH, game);
		if (dist != -1)
		{
			draw(a, angle, WIDTH, game);
			// draw_line(a, angle, game);
			printf("Dst to angle %.0f -> %f\n", angle, dist);
		}
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
		"101N01   101",
		"110001    1",
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
