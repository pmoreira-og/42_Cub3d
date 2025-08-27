#include "../../include/cub3d.h"

/// @brief setup and getting raw content from input file
/// @param parse struct with everything needed for the parse
/// @return true on success, false on failure
bool	setup_for_extraction(t_parse *parse)
{
	parse->fd = open(parse->path, O_RDONLY);
	if (parse->fd < 3)
		return (printf_fd(2, M_NOOP), false);
	parse->lc = get_file_line_count(parse->fd);
	if (parse->lc < 9)
		return (printf_fd(2, M_ERRO M_LC), false);
	parse->fd = open(parse->path, O_RDONLY);
	if (parse->fd < 3)
		return (printf_fd(2, M_NOOP), false);
	parse->literal = file_literal_copy(parse->fd, parse->lc);
	if (!parse->literal)
		return (printf_fd(2, M_MFL), false);
	return (printf_fd(2, "survived setup\n"), true);
}

/// @return number of lines in the FD file
int	get_file_line_count(int fd)
{
	int		lc;
	char	*file_line;

	lc = 0;
	while (1)
	{
		file_line = get_next_line(fd);
		if (!file_line)
			break ;
		free(file_line);
		lc++;
	}
	safe_close(fd);
	return (lc);
}

/// @brief makes a literal copy of the content in the FD file
/// @param fd file to copy from
/// @param lc number of lines in the FD file
/// @return
char	**file_literal_copy(int fd, int lc)
{
	char	**copy;
	char	*line;
	int		i;

	copy = ft_calloc(lc + 1, sizeof(char *));
	if (!copy)
		return (safe_close(fd), NULL);
	i = -1;
	while (++i < lc)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		copy[i] = line;
	}
	safe_close(fd);
	return (copy);
}
