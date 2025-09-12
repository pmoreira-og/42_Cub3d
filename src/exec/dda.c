#include "../../include/cub3d.h"

/// @brief Get absolute value of a double type number.
double	ft_abs(double nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	return (nbr);
}

double	collider_dda(t_player p, double cameraX, t_game *g, t_dda *dda)
{
	init_struct(dda, &p, cameraX);
	get_step(dda, &p);
	while (!dda->hit)
	{
		next_step(dda);
		if (dda->map_x < 0 || dda->map_x >= g->map_width || dda->map_y < 0
			|| dda->map_y >= g->map_height)
			return (-1.0);
		has_collided(dda, g, &p);
	}
	if (!isfinite(dda->perp_dist) || dda->perp_dist < 0.0)
		return (-1.0);
	save_hit_pos(dda, &p);
	if (dda->perp_dist < 1e-6)
		dda->perp_dist = 1e-6;
	return (0);
}

t_cord	collider_angle(t_img_data *bg, t_cord cord, double angle,
		double max_dist)
{
	t_cord	inc;
	bool	colidded;
	int		i;

	inc.x = cos(angle);
	inc.y = -sin(angle);
	colidded = false;
	i = -1;
	while (++i <= (int)max_dist)
	{
		if (minimap_collider(bg, cord))
			colidded = true;
		if (!colidded)
			put_pixel(bg, cord.x, cord.y, 0x00FF00);
		cord.x += inc.x;
		cord.y += inc.y;
	}
	return (cord);
}

bool	draw_line(t_img_data *bg, t_cord start, t_cord end)
{
	t_cord	inc;
	double	steps;
	int		i;

	inc.x = end.x - start.x;
	inc.y = end.y - start.y;
	if (ft_abs(inc.x) >= ft_abs(inc.y))
		steps = ft_abs(inc.x);
	else
		steps = ft_abs(inc.y);
	inc.x /= steps;
	inc.y /= steps;
	i = -1;
	while (++i <= steps)
	{
		if (minimap_collider(bg, start))
			return (false);
		put_pixel(bg, start.x, start.y, 0x00FF00);
		start.x += inc.x;
		start.y += inc.y;
	}
	return (true);
}

bool	minimap_collider(t_img_data *bg, t_cord pos)
{
	int	color;

	// did this so i can add more "collision colors"
	color = get_pixel(bg, pos.x, pos.y);
	if (color == 0)
		return (true);
	else
		return (false);
}

void	draw_circle(t_img_data *bg, t_cord cord, t_cord range, double radius)
{
	bool	clock_wise;
	t_cord	inc;

	if (range.x < range.y)
		clock_wise = true;
	else
		clock_wise = false;
	while ((clock_wise && range.x < range.y) || (!clock_wise
			&& range.x > range.y))
	{
		inc.x = cos(range.x) * radius;
		inc.y = -sin(range.x) * radius;
		if (!minimap_collider(bg, (t_cord){cord.x + inc.x, cord.y + inc.y}))
			put_pixel(bg, cord.x + inc.x, cord.y + inc.y, 0x00FF00);
		if (clock_wise)
			range.x += 0.017;
		else
			range.x -= 0.017;
	}
}
