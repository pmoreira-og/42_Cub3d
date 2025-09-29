/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:22:24 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/09/29 18:22:25 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac > 3 || (ac == 3 && ft_strcmp("-d", av[2])) || ac < 2)
		return (printf_fd(2, M_ARGAMT M_USAGE), 2);
	if (!get_map(&game, av[1]))
		return (1);
	if (!setup_mlx(&game))
		return (cleanup_all(&game), 1);
	if (ac == 3)
		game.debug = 1;
	if (game.debug)
		print_map(&game);
	manager(&game);
	mlx_loop_hook(game.mlx, render_map, &game);
	mlx_loop(game.mlx);
	return (0);
}
