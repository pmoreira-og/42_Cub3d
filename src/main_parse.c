#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	ft_printf("Hello Parse World\n");
	t_game	game;

	if (ac > 3 || (ac == 3 && ft_strcmp("-d", av[2])) || ac < 2 )
		return (printf_fd(2, M_ARGAMT M_USAGE), 2);
	if (!get_map(&game, av[1]))
		return (1);
	if (!setup_mlx(&game))
		return (armageddon(&game), 1);
	// sleep(3);
	return (printf_fd(2, "survived main\n"), armageddon(&game), 0);
}
