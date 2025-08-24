#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	ft_printf("Hello Parse World\n");
	t_game	game;

	if (ac > 3 || (ac == 3 && ft_strcmp("-d", av[2])) || ac < 2 )
		return (printf_fd(2, M_ARGAMT M_USAGE), 2);
	(void)game;
	ft_printf("valid av\n");
	if (!get_map(&game, av[1]))
		return (1);
	return (printf_fd(2, "survived main\n"), armageddon(&game), 0);
}

void	manager(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_win_mouse, game);
	mlx_hook(game->win, 2, 1L << 0, key_press_manager, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_manager, game);
}

int	render_map(t_game *game)
{
	t_point	a;

	move_handler(game);
	if (!is_moved(game))
		return (1);
	if (game->bg && !get_next_img(game))
		return (0);
	a.x = game->player.pos_x;
	a.y = game->player.pos_y;
	double angle = game->player.direction - 45;
	double dist = 0;
	t_point	hit;
	while (angle <= game->player.direction + 45)
	{
		put_pixel(game->bg, a.x, a.y, 0x00FF00);
		dist = collider_dda(a, angle, game, &hit);
		if (dist != -1)
			draw(a, angle, WIDTH, game);
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