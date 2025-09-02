
#pragma once

// -‵,┊  main library
#include "cub3d.h"
#include <stdbool.h>
#include <unistd.h>

// -->┊( STRUCTS )┊.´-★☆★

/// @brief Types of map elements.
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
	double		y;
	double		x;
	t_type		type;
}				t_point;

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			len;
	int			endian;
	int			width;
	int			height;
}				t_img_data;

/// @brief Stores all colected header elements.
typedef struct s_header
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor;
	int			ceiling;
}				t_header;

/// @brief Everything needed for the parse
typedef struct s_parse
{
	char		*path;
	int			fd;
	int			lc;
	t_header	hd;
	size_t		heigth;
	size_t		width;
	int			margin_l;
	int			margin_r;
	char		**literal;
	char		**map_st;
	char		**padded;
	t_type		player;
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
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_dist;
	double		dx;
	double		dy;
	double		map_x;
	double		map_y;
	int			step_x;
	int			step_y;
	int			side;
	bool		hit;
	t_point		hit_point;
}				t_dda;

typedef struct s_wall
{
	double		wall_x;
	double		tex_x;
	double		tex_y;
	double		step;
	double		tex_pos;
	t_img_data	*texture;
	int			color;
	int			start;
	int			end;
	int			height;
}				t_wall;

/// @brief Struct to save player info.
/// @param pos_x Position of the player on the map in X axis.
/// @param pos_y Position of the player on the map in Y axis.
/// @param direction angle (in rad) where the player is looking.
typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			plane_mag;
	double			direction;
	int				m_forward;
	int				m_back;
	int				m_left;
	int				m_right;
	int				rot_right;
	int				rot_left;
}					t_player;

typedef struct s_minimap
{
	int			offset;
	int			tile;
	int			width;
	int			height;
	t_player	p;
}					t_minimap;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_point		**matrix;
	size_t		map_height;
	size_t		map_width;
	double		scale;
	t_img_data	bg;
	t_player	player;
	t_minimap		mini;
	int			floor_color;
	int			ceiling_color;
	t_img_data	walls[4];
	char		*paths[4];
	bool		debug;
}				t_game;