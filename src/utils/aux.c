#include "../../include/cub3d.h"



/// @brief Prints malloc error message on stderr.
/// @param msg Message for malloc debug porposes.
void	merror(char *msg)
{
	if (msg)
		printf_fd(2, "Malloc:%s\n", msg);
}

