#include "../include/cub3d.h"


int	main(int ac, char **av)
{
	t_game	game;

	if (ac > 3 || (ac == 3 && ft_strcmp("-d", av[2])) || ac < 2 )
		return (printf_fd(2, M_ARGAMT M_USAGE), 2);
	if (!get_map(&game, av[1]))
		return (1);
	if (!setup_mlx(&game))
		return (armageddon(&game), 1);
	if (ac == 3)
		game.debug = 1;
	if(game.debug)
		print_map(&game);
	manager(&game);
	mlx_loop_hook(game.mlx, render_map, &game);
	mlx_loop(game.mlx);
	return (0);
}
