
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
}				t_img_data;

typedef struct s_rgb
{
	int			R;
	int			G;
	int			B;
}				t_rgb;

typedef struct s_texture
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
}				t_texture;

typedef struct s_colors
{
	t_rgb		floor;
	t_rgb		ceiling;
}				t_colors;

typedef struct s_parse
{
	int 		fd;
	int 		lc;
	char		*path;
	t_texture	tx;
	t_colors	cl;
	size_t 		heigth;
	size_t 		width;
	char		**literal;
	int 		start;
	char		**padded;
}				t_parse;

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
