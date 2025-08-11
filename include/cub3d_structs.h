/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:22:02 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/08/11 15:21:49 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// -‵,┊  main library
#include "cub3d.h"

// -->┊( STRUCTS )┊.´-★☆★
typedef enum e_type
{
	VOID,
	WALL,
	FLOOR,
	PLAYER_N,
	PLAYER_S,
	PLAYER_E,
	PLAYER_W
}				t_type;

/// @brief Structure that has the point information.
typedef struct s_point
{
	int		y;
	int		x;
	t_type	type;
}	t_point;

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			len;
	int			endian;
}				t_img_data;	// Direction vector


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

typedef struct s_dda
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	double	dx;
	double	dy;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	bool	hit;
}				t_dda;


typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	t_point		**matrix;
	size_t		map_width;
	size_t		map_height;
	double		scale;
	t_img_data	*bg;
	int			file_fd;
	bool		debug;
}				t_game;
