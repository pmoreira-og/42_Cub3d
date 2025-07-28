
#include "../../include/cub3d.h"

/// @brief Get absolute value of a double type number.
static double	ft_abs(double nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	return (nbr);
}

void	draw_line(t_img_data *img, t_point start, t_point end, int color)
{
	double	dx;
	double	dy;
	double	steps;
	double	coord[2];
	int		i;

	dx = end.x - start.x;
	dy = end.y - start.y;
	if (ft_abs(dx) >= ft_abs(dy))
		steps = ft_abs(dx);
	else
		steps = ft_abs(dy);
	dx /= steps;
	dy /= steps;
	coord[0] = start.x;
	coord[1] = start.y;
	i = -1;
	while (++i <= steps)
	{
		if (coord[0] >= 0 && coord[0] < WIDTH
			&& coord[1] >= 0 && coord[1] < HEIGHT)
			put_pixel(img, (int) coord[0], (int) coord[1], color);
		coord[0] += dx;
		coord[1] += dy;
	}
}

bool	check_colision(double x0, double y0, t_point **map, t_point **hit)
{
	int	x;
	int	y;

	x = (int) x0;
	y = (int) y0;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		if (map[y][x].type == WALL)
		{
			*hit = &map[y][x];
			return (true);
		}
	}
	return (false);
}

/// @brief Raycasting function that uses DDA algorithm to check colision.
/// @param hit Address of a pointer to saves where the colision occured.
/// @return True on colision.
bool	raycast(t_point start, t_point end, t_point **map, t_point **hit)
{
	double	d[2];
	double	coord[2];
	double	steps;
	int		i;

	d[0] = end.x - start.x;
	d[1] = end.y - start.y;
	if (ft_abs(d[0]) >= ft_abs(d[1]))
		steps = ft_abs(d[0]);
	else
		steps = ft_abs(d[1]);
	d[0] /= steps;
	d[1] /= steps;
	coord[0] = start.x;
	coord[1] = start.y;
	i = -1;
	while (++i <= steps)
	{
		if (check_colision(coord[0], coord[1], map, hit))
			return (true);
		coord[0] += d[0];
		coord[1] += d[1];
	}
	return (false);
}
