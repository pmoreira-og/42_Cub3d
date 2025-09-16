#include "../../include/cub3d.h"

double	deg2rad(double angle)
{
	return (angle * (PI / 180));
}

double	normalize_rad(double rad)
{
	double	inc;

	if (rad < 0)
		inc = 2 * PI;
	else
		inc = -2 * PI;
	while (rad >= 2 * PI || rad < 0)
		rad += inc;
	return (rad);
}

/// @brief Get absolute value of a double type number.
double	ft_abs(double nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	return (nbr);
}

static long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf_fd(2, "gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

bool	time_passed(int gap)
{
	static long	latest;
	long		curr;

	curr = get_current_time();
	if (curr - latest > gap)
	{
		latest = curr;
		return (true);
	}
	else
		return (false);
}
