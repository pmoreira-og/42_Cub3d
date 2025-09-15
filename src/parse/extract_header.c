#include "../../include/cub3d.h"

/// @brief extracts the 6 needed ids and sees if their content is valid
/// @return true on success, false on failure
bool	extract_header(t_parse *parse)
{
	int	i;
	int	info;

	i = -1;
	info = 0;
	while (parse->literal[++i] && info != 6)
	{
		if (!ft_strcmp(parse->literal[i], "\n"))
			continue ;
		if (!valid_identifier(&parse->hd, parse->literal[i]))
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
	return (true);
}

/// @brief sees if LINE starts with "NO ", "SO ", "WE ", "EA ", "F " or "C "
/// @param hd header struct where to store the info after the id
/// @param line containing the texture identifier and path
/// @return true when valid, false when invalid
bool	valid_identifier(t_header *hd, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
	{
		return (extract_path(hd, line));
	}
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
	{
		return (extract_color(hd, line));
	}
	return (printf_fd(2, M_ERRO M_INVID), false);
}

/// @brief gets path from PATH and sees if its an existing .xpm file
/// @param tx header struct containig the textures
/// @param path full line with texture identifier and path
/// @return true on success, false on failure
bool	extract_path(t_header *tx, char *path)
{
	char	**type;
	int		fd;
	int		i;

	type = assign_direction(path, tx);
	if (*type)
		return (printf_fd(2, M_ERRO M_REP), false);
	i = 3;
	while (path[i] == ' ')
		i++;
	*type = ft_strndup(&path[i], len_until(&path[i], '\n'));
	if (!*type)
		return (printf_fd(2, M_MFL), false);
	if (ft_strncmp(".xpm", *type + ft_strlen(*type) - 4, 4))
		return (printf_fd(2, M_ERRO M_NOXPM), false);
	fd = open(*type, O_RDONLY);
	if (fd < 3)
		return (printf_fd(2, M_ERRO M_NOOPTX), false);
	return (safe_close(fd), true);
}

/// @brief according to DIR sees which texture this is
/// @param dir can be either "NO ", "SO ", "WE " or "EA "
/// @param tx header struct containig possible textures
/// @return pointer to where that texture should be stored
char	**assign_direction(char *dir, t_header *tx)
{
	if (!ft_strncmp(dir, "NO ", 3))
		return (&tx->no);
	else if (!ft_strncmp(dir, "SO ", 3))
		return (&tx->so);
	else if (!ft_strncmp(dir, "WE ", 3))
		return (&tx->we);
	else if (!ft_strncmp(dir, "EA ", 3))
		return (&tx->ea);
	else
		return (NULL);
}
