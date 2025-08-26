#include "../../include/cub3d.h"

bool	extract_color(t_colors *cl, char *code)
{
	int		i;
	int		color_len;
	char	color[12];
	t_rgb	*type;

	type = NULL;
	if (!ft_strncmp(code, "F ", 2))
		type = &cl->floor;
	else if (!ft_strncmp(code, "C ", 2))
		type = &cl->ceiling;
	if (type->R != -1 || type->G != -1 || type->B != -1)
		return (printf_fd(2, M_ERRO M_REP), false);
	i = 2;
	while (code[i] == ' ')
		i++;
	color_len = len_until(&code[i], '\n');
	if (color_len < 5 || color_len > 11)
		return (printf_fd(2, M_ERRO M_COLF), false);
	ft_bzero(color, sizeof(color));
	ft_memcpy(color, &code[i], color_len);
	if (!valid_color_format(color))
		return (printf_fd(2, M_ERRO M_COLF), false);
	if (!assign_color_code(color, type))
		return (printf_fd(2, M_ERRO M_COLF), false);
	return (true);
}

bool	valid_color_format(char *code)
{
	int	i;
	int	j;
	int	field;
	int	num_len;

	i = 0;
	field = -1;
	while (++field < 3)
	{
		j = -1;
		num_len = len_until(&code[i], ',');
		if (num_len < 1 || num_len > 3 || (field < 2 && code[i
				+ num_len] != ',') || (field == 2 && code[i + num_len]))
			return (false);
		while (++j < num_len)
			if (!ft_isdigit(code[i + j]))
				return (false);
		i += num_len + 1;
	}
	return (true);
}

bool	assign_color_code(char *code, t_rgb *type)
{
	char	color[4];
	int		num_len;
	int		param;
	int		val;

	param = 1;
	while (*code)
	{
		ft_bzero(color, sizeof(color));
		num_len = len_until(code, ',');
		ft_memcpy(color, code, num_len);
		val = ft_atoi(color);
		if (val > 255)
			return (false);
		if (param == 1)
			type->R = val;
		else if (param == 2)
			type->G = val;
		else if (param == 3)
			type->B = val;
		param++;
		code += num_len + 1;
	}
	// ft_printf("color is: R%d G%d B%d\n", type->R, type->G, type->B);
	return (true);
}
