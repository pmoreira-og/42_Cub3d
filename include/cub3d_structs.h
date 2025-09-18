
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

/// @brief Types of scenes that can be rendered
typedef enum e_scene
{
	MENU,
	GAME,
	PAUSE
}				t_scene;

typedef struct s_cord
{
	double		x;
	double		y;
}				t_cord;

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
	int			heigth;
	int			width;
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
	t_cord		ray_dir;
	t_cord		side_dist;
	double		perp_dist;
	t_cord		d;
	t_cord		map;
	int			step_x;
	int			step_y;
	int			side;
	bool		hit;
	t_point		hit_point;
}				t_dda;

typedef struct s_wall
{
	double		wall_x;
	t_cord		tex;
	double		step;
	double		tex_pos;
	t_img_data	*texture;
	int			color;
	int			start;
	int			end;
	int			height;
	double		light;
	double		dist_intensity;
	double		ang_intensity;
}				t_wall;

/// @brief Struct with variables need to bob effect.
typedef struct s_bob
{
	double		phase;
	double		curr_amp;
	double		cam_pitch;
	t_cord		prev;
}				t_bob;

typedef struct s_action
{
	bool		m_forward;
	bool		m_back;
	bool		m_left;
	bool		m_right;
	bool		rot_right;
	bool		rot_left;
	bool		sneaking;
	bool		sprint;
}				t_action;

/// @brief Struct to save player info.
/// @param pos_x Position of the player on the map in X axis.
/// @param pos_y Position of the player on the map in Y axis.
/// @param direction angle (in rad) where the player is looking.
typedef struct s_player
{
	t_cord		pos;
	t_cord		dir;
	t_cord		plane;
	double		plane_mag;
	double		direction;
	t_action	act;
	int			vertical_view;
	double		flash_fov;
	double		cos_flash;
	bool		flash_on;
	t_bob		bob;
}				t_player;

/// @brief Struct for drawing a circle
/// @param cord center cordinates
/// @param angle_from where to start the circle (rad)
/// @param angle_to where to stop the circle (rad)
/// @param radius
/// @param color
typedef struct s_circle
{
	t_cord		cord;
	double		angle_from;
	double		angle_to;
	double		radius;
	int			color;
}				t_circle;

/// @brief Struct to render the minimap
/// @param show on and off toggle
/// @param bg image to render on
/// @param p needed for pos and dir
/// @param m map matrix
/// @param m_h map heigth
/// @param m_w map width
/// @param scale can be either 1 or 3
/// @param offset gap to the left/top of the map
/// @param center of player in the minimap
typedef struct s_minimap
{
	bool		show;
	t_img_data	*bg;
	t_player	*p;
	t_point		***m;
	int			m_h;
	int			m_w;
	int			scale;
	int			offset;
	t_cord		size;
	t_cord		center;
}				t_minimap;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_point		**matrix;
	int			map_height;
	int			map_width;
	t_img_data	bg;
	t_img_data	menu;
	t_img_data	hand[2];
	t_player	player;
	t_minimap	mini;
	int			floor_color;
	int			ceiling_color;
	t_img_data	walls[4];
	char		*paths[4];
	t_scene		scene;
	bool		debug;
	double		move_speed;
	double		rot_speed;
}				t_game;
