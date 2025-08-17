#include "../../include/cub3d.h"

bool	extract_map(t_parse *parse)
{
	// start saving the map to a char **
	// -- see if it uses anything besides 0 1 N S E W ' '(space) and '\n'
	safe_close(parse->fd);
	return (printf_fd(2, "survived map\n"), false);
}
