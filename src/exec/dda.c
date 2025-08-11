
#include "../../include/cub3d.h"

/// @brief Get absolute value of a double type number.
// static double	ft_abs(double nbr)
// {
// 	if (nbr < 0)
// 		return (nbr * -1);
// 	return (nbr);
// }

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

/// @brief Raycasting collision checker based on trigonometric circle angles.
/// @param start Start point where the line gonna start.
/// @param angle Trigonometric circle based angle.
/// @param max_dist Max distance of the line to check collision.
/// @param game Main struct.
/// @return 
double	collider_angle(t_point start, double angle, double max_dist,
	t_game *game)
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
		if (check_colision(coord[0], coord[1], game, NULL))
			return (i);
		coord[0] += inc[0];
		coord[1] += inc[1];
	}
	return (-1);
}

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
double	collider_dda(t_point start, double angle, double max_dist,
	t_game *game, t_point *hit)
{
	// Direction vector
	double ray_dir_x = cos(angle * (PI / 180));
	double ray_dir_y = -sin(angle * (PI / 180));

	// Current map cell
	int map_x = (int)(start.x / game->scale);
	int map_y = (int)(start.y / game->scale);

	// Length of ray from one x or y-side to next x or y-side
	double delta_dist_x = fabs(1.0 / ray_dir_x);
	double delta_dist_y = fabs(1.0 / ray_dir_y);

	// Step direction and initial sideDist
	int step_x, step_y;
	double side_dist_x, side_dist_y;

	// Calculate step and initial side_dist
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (start.x / game->scale - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = ((map_x + 1.0) - start.x / game->scale) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (start.y / game->scale - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = ((map_y + 1.0) - start.y / game->scale) * delta_dist_y;
	}

	int collision = 0;
	int side = 0; // 0 = x-side, 1 = y-side
	double perp_wall_dist = 0;

	while (!collision)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}

		// Check if ray is out of bounds
		if (map_x < 0 || map_x >= (int)game->map_width
			|| map_y < 0 || map_y >= (int)game->map_height)
			break;

		// Check for wall hit
		if (game->matrix[map_y][map_x].type == WALL)
		{
			collision = 1;
			if (side == 0)
				perp_wall_dist = (map_x - start.x / game->scale + (1 - step_x) / 2) / ray_dir_x;
			else
				perp_wall_dist = (map_y - start.y / game->scale + (1 - step_y) / 2) / ray_dir_y;
		}
	}

	if (!collision || perp_wall_dist < 0 || perp_wall_dist > max_dist)
		return -1;

	// Compute exact hit position in world coordinates
	if (side == 0)
	{
		hit->x = map_x * game->scale;
		hit->y = start.y + perp_wall_dist * ray_dir_y * game->scale;
	}
	else
	{
		hit->x = start.x + perp_wall_dist * ray_dir_x * game->scale;
		hit->y = map_y * game->scale;
	}

	return perp_wall_dist * game->scale;
}
