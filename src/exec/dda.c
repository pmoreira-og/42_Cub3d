
#include "cub3d.h"

/// @brief Get absolute value of a long type number.
/// @return Return absolute value or LONG_MAX if nbr == LONG_MIN
static long	ft_abs(long nbr)
{
	if (nbr == LONG_MIN)
		return (LONG_MAX);
	if (nbr < 0)
		return (nbr * -1);
	return (nbr);
}

void	draw_line(t_point start, t_point end, int color)
{
	long	dx;
	long	dy;
	long	steps;
	steps = ft_abs()
}