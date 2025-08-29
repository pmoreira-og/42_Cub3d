
#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H

// -‵,┊  main library
# include "cub3d.h"

// -->┊( DEFINES )┊.´-★☆★

# define TITLE "Absolute Cinema3D"
# define LOGO "./textures/logo_cub3d.xpm"
# define EASTER "./textures/easter_egg.xpm"
# define DUCK "./textures/duck.xpm"
# define TEST "./textures/north.xpm"
# define GRID "./textures/grid.xpm"
# define WIDTH 1440
# define HEIGHT 1080
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define VK_UP 65362
# define VK_DOWN 65364
# define VK_LEFT 65361
# define VK_RIGHT 65363
# define ESC 65307
# define KEY_1 49
# define KEY_2 50
# define KEY_3 51
# define KEY_4 52
# define SRC_UP 4
# define SRC_DOWN 5
# define KEY_T 116
# define KEY_Y 121
# define PI 3.14159265358979323846
# define FOV 66
# define PLAYER_RADIUS_TILES 0.1
# ifndef MOVESPEED
#  define MOVESPEED 1
# endif
# ifndef ROTSPEED
#  define ROTSPEED 1
# endif

//-‵,┊ colors

# define DEF "\e[0m"

// ★☆★ regular text

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

// ★☆★ regular underline text

# define UBLK "\e[4;30m"
# define URED "\e[4;31m"
# define UGRN "\e[4;32m"
# define UYEL "\e[4;33m"
# define UBLU "\e[4;34m"
# define UMAG "\e[4;35m"
# define UCYN "\e[4;36m"
# define UWHT "\e[4;37m"

// ★☆★ regular bold text

# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define BWHT "\e[1;37m"

// ★☆★ high intensty text

# define HBLK "\e[0;90m"
# define HRED "\e[0;91m"
# define HGRN "\e[0;92m"
# define HYEL "\e[0;93m"
# define HBLU "\e[0;94m"
# define HMAG "\e[0;95m"
# define HCYN "\e[0;96m"
# define HWHT "\e[0;97m"

// ★☆★ bold high intensity text

# define BHBLK "\e[1;90m"
# define BHRED "\e[1;91m"
# define BHGRN "\e[1;92m"
# define BHYEL "\e[1;93m"
# define BHBLU "\e[1;94m"
# define BHMAG "\e[1;95m"
# define BHCYN "\e[1;96m"
# define BHWHT "\e[1;97m"

//-‵,┊ bg colors

// ★☆★ regular background

# define BLKB "\e[40m"
# define REDB "\e[41m"
# define GRNB "\e[42m"
# define YELB "\e[43m"
# define BLUB "\e[44m"
# define MAGB "\e[45m"
# define CYNB "\e[46m"
# define WHTB "\e[47m"

// ★☆★ high intensty background

# define BLKHB "\e[0;100m"
# define REDHB "\e[0;101m"
# define GRNHB "\e[0;102m"
# define YELHB "\e[0;103m"
# define BLUHB "\e[0;104m"
# define MAGHB "\e[0;105m"
# define CYNHB "\e[0;106m"
# define WHTHB "\e[0;107m"

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

#endif