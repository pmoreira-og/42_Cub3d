#include "../../include/cub3d.h"

/// @brief draws a block of color
/// @param bg img where to draw
/// @param color color of the block
/// @param area dimentions of the block
/// @param win cordinate where to start drawing
void	draw_colorblock(t_img_data *bg, int color, t_cord area, t_cord win)
{
	int	wid;
	int	hei;

	hei = -1;
	while (++hei < area.y)
	{
		wid = -1;
		while (++wid < area.x)
			put_pixel(bg, win.x + wid, win.y + hei, color);
	}
}

/// @brief draws a 3 pixel wide inside frame
/// @param bg img where to draw
/// @param color color of the frame
/// @param area dimentions of the frame
/// @param win cordinate where to start drawing
void	draw_colorframe(t_img_data *bg, int color, t_cord area, t_cord win)
{
	int	wid;
	int	hei;

	hei = -1;
	while (++hei < area.y)
	{
		wid = -1;
		while (++wid < area.x)
		{
			if (hei < 3 || hei > area.y - 4 || wid < 3 || wid > area.x - 4)
				put_pixel(bg, win.x + wid, win.y + hei, color);
			if (hei >= 3 && hei <= area.y - 4 && wid >= 3 && wid <= area.x - 4)
				wid = area.x - 4;
		}
	}
}

/// @brief draw a line from CORD at ANGLE degrees for LEN length
/// @param bg img where to draw
/// @param cord cordinate where to start drawing
/// @param angle angle of the line in rad
/// @param len length of the line
void	draw_angled_line(t_img_data *bg, t_cord cord, double angle, double len)
{
	t_cord	inc;
	int		i;

	inc.x = cos(angle);
	inc.y = -sin(angle);
	i = -1;
	while (++i <= (int)len)
	{
		put_pixel(bg, cord.x, cord.y, 0xFBFE8D);
		cord.x += inc.x;
		cord.y += inc.y;
	}
}

/// @brief draws a circle according to C
/// @param bg img where to draw
/// @param c struct with all info needed for the circle
void	draw_circle(t_img_data *bg, t_circle c)
{
	bool	clock_wise;
	t_cord	inc;

	if (c.angle_from < c.angle_to)
		clock_wise = true;
	else
		clock_wise = false;
	while ((clock_wise && c.angle_from < c.angle_to) || (!clock_wise
			&& c.angle_from > c.angle_to))
	{
		inc.x = cos(c.angle_from) * c.radius;
		inc.y = -sin(c.angle_from) * c.radius;
		put_pixel(bg, c.cord.x + inc.x, c.cord.y + inc.y, c.color);
		if (clock_wise)
			c.angle_from += 0.01;
		else
			c.angle_from -= 0.01;
	}
}

/// @brief starting from CORD it fills with COLOR every occurence of ONLY
void	bucket_tool(t_img_data *bg, t_cord cord, int color, int only)
{
	int	pixel;

	if (cord.x < 0 || cord.y < 0 || cord.x > WIDTH || cord.y > HEIGHT)
		return ;
	pixel = get_pixel(bg, (int)cord.x, (int)cord.y);
	if (pixel == color || pixel != only)
		return ;
	put_pixel(bg, (int)cord.x, (int)cord.y, color);
	bucket_tool(bg, (t_cord){cord.x + 1, cord.y}, color, only);
	bucket_tool(bg, (t_cord){cord.x - 1, cord.y}, color, only);
	bucket_tool(bg, (t_cord){cord.x, cord.y + 1}, color, only);
	bucket_tool(bg, (t_cord){cord.x, cord.y - 1}, color, only);
}
