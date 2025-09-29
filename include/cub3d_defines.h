
#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H

// -‵,┊  main library
# include "cub3d.h"

// -->┊( DEFINES )┊.´-★☆★

//-‵,┊ values

# define WIDTH 1440
# define HEIGHT 1080
# define TRANSPARENT 0xFF000000
# define PI 3.14159265358979323846
# define FOV 66
# define FLASH_FOV 60
# define PLAYER_RADIUS_TILES 0.1
# define MOVESPEED 0.05
# define ROTSPEED 2
# define SMOOTH 0.25
# define TARGET_AMP 7.0
# define CYCLE_LENGTH 1.05
# ifndef HIDE
#  define HIDE 0
# endif

//-‵,┊ assets

# define TITLE "Night at the Aquarium"
# define MAIN_MENU "./assets/main_menu_"
# define LANTERN "./assets/lantern_"

//-‵,┊ key codes

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define VK_UP 65362
# define VK_DOWN 65364
# define VK_LEFT 65361
# define VK_RIGHT 65363
# define VK_UP 65362
# define VK_DOWN 65364
# define SHIFT 65505
# define BACKSPACE 65288
# define VK_CTRL 65507
# define ENTER 65293
# define ESC 65307

//-‵,┊ text colors

# define DEF "\e[0m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"

//-‵,┊ messages

# define M_ARGAMT "incorrect amount of arguments provided!\n"
# define M_USAGE \
	"usage: ./cub3D [path to .cub map file] [-d option \
	(optional)]\n"
# define M_FEXT \
	"incorrect file extention in inputed map path, \
	needs to be .cub\n"
# define M_NOOP "couldn't open inputed map\n"
# define M_ERRO "Error\n"
# define M_LC "insuficient lines\n"
# define M_MFL "malloc: failure\n"
# define M_HEAD "wasn't able to get header info\n"
# define M_INVID "invalid identifier\n"
# define M_REP "repeated identifier\n"
# define M_NOXPM "incorrect file extention in texture file, needs to be .xpm\n"
# define M_NOOPTX "couldn't open inputed texture file\n"
# define M_COLF "incorrect color format\n"
# define M_NOTINF "not all necessary information found\n"
# define M_MAPSZ "insuficient map size\n"
# define M_MAPEMP "empty line in the map\n"
# define M_MAPCH "invalid characters found in map\n"
# define M_PPOS "repeated player position\n"
# define M_MPPOS "missing player position\n"
# define M_WALLS "missing surrounding walls\n"
# define M_MLXINITF "failure in MLX initialization\n"
# define M_MLXWINDF "failure in MLX window creation\n"
# define M_INVXPM "couldn't load an xpm texture\n"
# define M_MLXIMGF "failure in MLX image creation\n"
# define M_MLXADRF "failure in MLX image adress extraction\n"

#endif