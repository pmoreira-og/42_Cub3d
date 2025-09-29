/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:14:57 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/09/29 18:19:48 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	clean_mlx(t_game *data);
static void	clean_assest(t_game *data);

void	cleanup_all(t_game *data)
{
	if (data->mlx)
		clean_mlx(data);
	if (data->matrix)
		free_matrix((void **)data->matrix);
	free(data->paths[0]);
	free(data->paths[1]);
	free(data->paths[2]);
	free(data->paths[3]);
}

static void	clean_mlx(t_game *data)
{
	int	i;

	if (data->bg.img)
		mlx_destroy_image(data->mlx, data->bg.img);
	i = -1;
	while (++i < 4)
		if (data->walls[i].img)
			mlx_destroy_image(data->mlx, data->walls[i].img);
	clean_assest(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
}

static void	clean_assest(t_game *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (data->menu[i].img)
			mlx_destroy_image(data->mlx, data->menu[i].img);
	i = -1;
	while (++i < 2)
	{
		if (data->hand[i].img)
			mlx_destroy_image(data->mlx, data->hand[i].img);
		if (data->flash[i].img)
			mlx_destroy_image(data->mlx, data->flash[i].img);
	}
	if (data->pause.img)
		mlx_destroy_image(data->mlx, data->pause.img);
	if (data->mini.frame.img)
		mlx_destroy_image(data->mlx, data->mini.frame.img);
}
