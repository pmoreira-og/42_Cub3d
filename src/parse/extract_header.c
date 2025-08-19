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
	while (!ft_strcmp(parse->literal[i], "\n"))
		i++;
	if (parse->lc - i < 3)
		return (printf_fd(2, M_ERRO M_MAPSZ M_HEAD), false);
	parse->map_st = &parse->literal[i];
	return (printf_fd(2, "survived header\n"), true);
}

bool	valid_identifier(t_parse *parse, char *line)
{
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

	type = assign_direction(path, tx);
	if (*type)
		return (printf_fd(2, M_ERRO M_REP), false);
	i = 3;
	while (path[i] == ' ')
		i++;
	*type = ft_strndup(&path[i], len_until(&path[i], '\n'));
	if (!*type)
		return (printf_fd(2, M_MFL), false);
	ft_printf("path is: %s\n", *type);
	if (ft_strncmp(".xpm", *type + ft_strlen(*type) - 4, 4))
		return (printf_fd(2, M_ERRO M_NOXPM), false);
	fd = open(*type, O_RDONLY);
	if (fd < 3)
		return (printf_fd(2, M_ERRO M_NOOPTX), false);
	return (safe_close(fd), true);
}

char	**assign_direction(char *dir, t_texture *tx)
{
	if (!ft_strncmp(dir, "NO ", 3))
		return (&tx->NO);
	else if (!ft_strncmp(dir, "SO ", 3))
		return (&tx->SO);
	else if (!ft_strncmp(dir, "WE ", 3))
		return (&tx->WE);
	else if (!ft_strncmp(dir, "EA ", 3))
		return (&tx->EA);
	else
		return (NULL);
}
