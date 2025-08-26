#include "../../include/cub3d.h"

bool	check_surrounding_walls(t_parse *parse)
{
	int	errors;
	int	y;
	int	x;

	errors = 0;
	y = -1;
	while (parse->padded[++y] && !errors)
	{
		x = -1;
		while (parse->padded[y][++x] && !errors)
		{
			if (parse->padded[y][x] == ' ')
			{
				// printf("sending flood on: y%d x%d\n", y, x);
				errors = space_flood_fill(y, x, parse);
			}
		}
	}
	// ft_printf("\nFILLED MAP:\n");
	// matrix_print(parse->padded);
	if (errors)
		return (false);
	return (true);
}

int	space_flood_fill(int y, int x, t_parse *parse)
{
	int	errors;

	if (y < 0 || y > (int)parse->heigth + 1 || x < 0 || x > (int)parse->width
		+ 1 || ft_strchr("12", parse->padded[y][x]))
		return (0);
	if (ft_strchr("0NSEW", parse->padded[y][x]))
		return (1);
	errors = 0;
	if (parse->padded[y][x] == ' ')
		parse->padded[y][x] = '2';
	errors += space_flood_fill(y + 1, x, parse);
	errors += space_flood_fill(y - 1, x, parse);
	errors += space_flood_fill(y, x - 1, parse);
	errors += space_flood_fill(y, x + 1, parse);
	return (errors);
}
