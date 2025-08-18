#include "../../include/cub3d.h"

bool	extract_header_info(t_parse *parse)
{
	int	i;
	int	info;

	i = -1;
	info = 0;
	while (parse->literal[++i] && info != 6)
	{
		if (!ft_strcmp(parse->literal[i], "\n"))
			continue ;
		if (!valid_identifier(parse, parse->literal[i]))
			return (printf_fd(2, M_HEAD), false);
		else
			info++;
	}
	if (info != 6)
		return (printf_fd(2, M_ERRO M_NOTINF M_HEAD), false);
	if (parse->lc - i < 3)
		return (printf_fd(2, M_ERRO M_MAPSZ M_HEAD), false);
	parse->start = i;
	return (printf_fd(2, "survived header\n"), true);
}

bool	valid_identifier(t_parse *parse, char *line)
{
	// compare all indentifiers
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
	{
		if (extract_path(&parse->tx, line, 0))
			return (true);
		else
			return (false);
	}
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
	{
		if (extract_color(&parse->cl, line))
			return (true);
		else
			return (false);
	}
	return (printf_fd(2, M_ERRO M_INVID), false);
}

bool	extract_path(t_texture *tx, char *path, int fd)
{
	int		i;
	char	**type;
	char	*texture;

	if (!ft_strncmp(path, "NO ", 3))
		type = &tx->NO;
	else if (!ft_strncmp(path, "SO ", 3))
		type = &tx->SO;
	else if (!ft_strncmp(path, "WE ", 3))
		type = &tx->WE;
	else if (!ft_strncmp(path, "EA ", 3))
		type = &tx->EA;
	if (*type)
		return (printf_fd(2, M_ERRO M_REP), false);
	i = 3;
	while (path[i] == ' ')
		i++;
	texture = ft_strndup(&path[i], len_until(&path[i], '\n'));
	if (!texture)
		return (printf_fd(2, M_MFL), false);
	ft_printf("path is: %s\n", texture);
	fd = open(texture, O_RDONLY);
	if (fd < 3)
		return (printf_fd(2, M_ERRO M_NOOPTX), false);
	*type = texture;
	return (safe_close(fd), true);
}

bool	extract_color(t_colors *cl, char *code)
{
	int		i;
	int		color_len;
	char	color[12];
	t_rgb	*type;

	
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

bool valid_color_format(char *code)
{
	int i;
	int j;
	int field;
	int num_len;

	i = 0;
	field = -1;
	while (++field < 3)
	{
		j = -1;
		num_len = len_until(&code[i], ',');
		if (num_len < 1 || num_len > 3 || \
			(field < 2 && code[i + num_len] != ',') || \
			(field == 2 && code[i + num_len]))
			return (false);
		while (++j < num_len)
			if (!ft_isdigit(code[i + j]))
				return (false);
		i += num_len + 1;
	}
	return (true);
}

bool assign_color_code(char *code, t_rgb *type)
{
	char color[4];
	int num_len;
	int param;
	int val;

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
	ft_printf("color is: R%d G%d B%d\n", type->R,type->G,type->B);
	return (true);
}
