/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:15:04 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/09/29 18:15:05 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*get_type_print(t_type type);

void	print_map(t_game *data)
{
	int	i;
	int	j;

	if (!data->matrix)
		return ;
	i = 0;
	ft_printf("\nGame Map:\n\n");
	ft_printf("Map Width: %d\n", data->map_width);
	ft_printf("Map Height: %d\n\n", data->map_height);
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			ft_printf("[%s]", get_type_print(data->matrix[i][j].type));
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}

static char	*get_type_print(t_type type)
{
	if (type == WALL)
		return (MAG "WALL" DEF);
	if (type == FLOOR)
		return (YEL "FLOR" DEF);
	if (type == PLAYER_E)
		return (BLU "PLYE" DEF);
	if (type == PLAYER_W)
		return (BLU "PLYW" DEF);
	if (type == PLAYER_N)
		return (BLU "PLYN" DEF);
	if (type == PLAYER_S)
		return (BLU "PLYS" DEF);
	if (type == VOID)
		return ("VOID");
	return ("");
}
