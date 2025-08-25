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
	
}

void	manager(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_win_mouse, game);
	mlx_hook(game->win, 2, 1L << 0, key_press_manager, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_manager, game);
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