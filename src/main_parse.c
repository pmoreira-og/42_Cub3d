#include "../include/cub3d.h"

# define M_ARGAMT	"incorrect amount of arguments provided!\n"
# define M_USAGE	"usage: ./cub3D [path to .cub map file] [-d option (optional)]\n"

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
	
}

void	manager(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_win_mouse, game);
	mlx_hook(game->win, 2, 1L << 0, close_win_keycode, game);
}

bool	render_map(t_game *game)
{
	t_point a;
	// t_point	*hit,b;
	find_player(game, &a);
	a.x *= game->scale;
	a.y *= game->scale;
	// b.x = a.x - 100;
	// b.y = a.y;
    printf("Player em: %d, %d\n", a.x, a.y);
	// if (collider(a, b, game, &hit))
	// {
	// 	draw_line(game->bg, a, *hit, 0xFF350C);
	// 	printf("Colidiu em: %d, %d\n", hit->x, hit->y);
	// }
	double angle = 0;
	while (angle <= 350)
	{
		if (collider_angle(a, angle, HEIGHT, game) != -1)
			draw(a, angle, HEIGHT, game);
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