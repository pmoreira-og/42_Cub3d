
#include "../../include/cub3d.h"

/// @brief Get absolute value of a double type number.
double	ft_abs(double nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	return (nbr);
}

// void	draw_line(t_img_data *img, t_point start, t_point end, int color)
// {
// 	double	dx;
// 	double	dy;
// 	double	steps;
// 	double	coord[2];
// 	int		i;

// 	dx = end.x - start.x;
// 	dy = end.y - start.y;
// 	if (ft_abs(dx) >= ft_abs(dy))
// 		steps = ft_abs(dx);
// 	else
// 		steps = ft_abs(dy);
// 	dx /= steps;
// 	dy /= steps;
// 	coord[0] = start.x;
// 	coord[1] = start.y;
// 	i = -1;
// 	while (++i <= steps)
// 	{
// 		if (coord[0] >= 0 && coord[0] < WIDTH
// 			&& coord[1] >= 0 && coord[1] < HEIGHT)
// 			put_pixel(img, (int) coord[0], (int) coord[1], color);
// 		coord[0] += dx;
// 		coord[1] += dy;
// 	}
// }

// *hit = &game->matrix[y][x];
// (*hit)->x *= game->scale;
// (*hit)->y *= game->scale;

static bool	check_colision(double x0, double y0, t_game *game, t_point **hit)
{
	int	x;
	int	y;

	x = (int)(x0 / game->scale);
	y = (int)(y0 / game->scale);
	(void) hit;
	if (x >= 0 && x < (int )game->map_width
		&& y >= 0 && y < (int )game->map_height)
	{
		if (game->matrix[y][x].type == WALL)
		{
			return (true);
		}
	}
	return (false);
}

// /// @brief Raycasting function that uses DDA algorithm to check colision.
// /// @param hit Address of a pointer to saves where the colision occured.
// /// @return True on colision.
// bool	collider(t_point start, t_point end, t_game *game, t_point **hit)
// {
// 	double	d[2];
// 	double	coord[2];
// 	double	steps;
// 	int		i;

// 	d[0] = end.x - start.x;
// 	d[1] = end.y - start.y;
// 	if (ft_abs(d[0]) >= ft_abs(d[1]))
// 		steps = ft_abs(d[0]);
// 	else
// 		steps = ft_abs(d[1]);
// 	d[0] /= steps;
// 	d[1] /= steps;
// 	coord[0] = start.x;
// 	coord[1] = start.y;
// 	i = -1;
// 	while (++i <= steps)
// 	{
// 		if (check_colision(coord[0], coord[1], game, hit))
// 			return (true);
// 		coord[0] += d[0];
// 		coord[1] += d[1];
// 	}
// 	*hit = NULL;
// 	return (false);
// }

// /// @brief Raycasting collision checker based on trigonometric circle angles.
// /// @param start Start point where the line gonna start.
// /// @param angle Trigonometric circle based angle.
// /// @param max_dist Max distance of the line to check collision.
// /// @param game Main struct.
// /// @return 
// double	collider_angle(t_point start, double angle, double max_dist,
// 	t_game *game)
// {
// 	double	inc[2];
// 	double	coord[2];
// 	int		i;

// 	inc[0] = cos(angle * (PI / 180));
// 	inc[1] = -sin(angle * (PI / 180));
// 	coord[0] = start.x;
// 	coord[1] = start.y;
// 	i = -1;
// 	while (++i <= (int)max_dist)
// 	{
// 		if (check_colision(coord[0], coord[1], game, NULL))
// 			return (i);
// 		coord[0] += inc[0];
// 		coord[1] += inc[1];
// 	}
// 	return (-1);
// }

void	draw(t_point start, double angle, double max_dist, t_game *game)
{
	double	inc[2];
	double	coord[2];
	int		i;

	inc[0] = cos(angle * (PI / 180));
	inc[1] = -sin(angle * (PI / 180));
	coord[0] = start.x;
	coord[1] = start.y;
	i = -1;
	while (++i <= (int)max_dist)
	{
		if (coord[0] >= 0 && coord[0] < WIDTH
			&& coord[1] >= 0 && coord[1] < HEIGHT)
			put_pixel(game->bg, (int) coord[0], (int) coord[1], 0xFFC000);
		if (check_colision(coord[0], coord[1], game, NULL))
			return ;
		coord[0] += inc[0];
		coord[1] += inc[1];
	}
}

double	collider_dda(t_point start, double angle, t_game *g, t_point *hit)
{
	t_dda	dda;

	init_struct(&dda, &start, g, angle);
	get_step(&dda, &start, g);
	while (!dda.hit)
	{
		next_step(&dda);
		if (dda.map_x < 0 || dda.map_x >= (int)g->map_width
			|| dda.map_y < 0 || dda.map_y >= (int)g->map_height)
			break ;
		has_collided(&dda, g, &start);
	}
	if (!dda.hit || dda.perp_wall_dist < 0 || dda.perp_wall_dist > WIDTH)
		return (-1);
	if (hit)
		save_hit_pos(&dda, hit, g, &start);
	return (dda.perp_wall_dist * g->scale);
}
