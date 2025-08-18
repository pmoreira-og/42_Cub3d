
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
	double	y;
	double	x;
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

/// @brief DDA Struct (Line = start + Direction * increment)
/// @param side 0 (X axis) 1 (Y axis)
/// @param ray_dir_y Direction where the vector grows on the Y axis
/// @param ray_dir_x Direction where the vector grows on the X axis
/// @param dx increment in X axis.
/// @param dy increment in Y axis.
/// @param step_x Grid Direction on X axis.
/// If ray_dir_x < 0: step = -1 (left).
/// @param step_y Grid Direction on Y axis.
typedef struct s_dda
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	double	dx;
	double	dy;
	double	map_x;
	double	map_y;
	int		step_x;
	int		step_y;
	int		side;
	bool	hit;
}				t_dda;

/// @brief Struct to save player info.
/// @param pos_x Position of the player on the map in X axis.
/// @param pos_y Position of the player on the map in Y axis.
/// @param direction angle where the player is looking.
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	direction;
	int		move_x;
	int		move_y;
	int		rotate;
	int		has_moved;
}				t_player;

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
	t_player	player;
	int			file_fd;
	bool		debug;
}				t_game;
