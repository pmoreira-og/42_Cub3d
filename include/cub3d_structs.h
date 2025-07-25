/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:22:02 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/07/25 15:09:28 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// -‵,┊  main library
#include "cub3d.h"

// -->┊( STRUCTS )┊.´-★☆★

/// @brief Structure that has the point information.
/// @param ord Position on the ordinate axis (Y).
/// @param abs Position on the abscissa axis (X).
typedef struct s_point
{
	int		ord;
	int		abs;
	int		color;
}	t_point;

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			len;
	int			endian;
}				t_img_data;

typedef struct s_rgb
{
	int			R;
	int			G;
	int			B;
}				t_rgb;

typedef struct s_textures
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
}				t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	size_t		map_width;
	size_t		map_height;
	t_img_data	*bg;
	int			file_fd;
}				t_game;
