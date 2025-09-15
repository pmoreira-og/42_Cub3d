#include "../../include/cub3d.h"

/// @brief gets map and all related info from the INPUT file
/// @param game game structure where to store the info
/// @param input used inputed path to file
/// @return true on success, false on failure
bool	get_map(t_game *game, char *input)
{
	t_parse	parse;

	if (ft_strncmp(".cub", input + ft_strlen(input) - 4, 4))
		return (printf_fd(2, M_FEXT), false);
	init_parse_struct(&parse, input);
	if (!setup_for_extraction(&parse))
		return (false);
	if (!extract_header(&parse))
		return (cleanup_parse(&parse), false);
	if (!extract_map(&parse))
		return (cleanup_parse(&parse), false);
	if (!map_to_game(&parse, game))
		return (cleanup_parse(&parse), armageddon(game), false);
	cleanup_parse(&parse);
	return (true);
}

/// @brief give default values for the parse struct
void	init_parse_struct(t_parse *parse, char *input)
{
	ft_bzero(parse, sizeof(t_parse));
	parse->path = input;
	parse->hd.floor = -1;
	parse->hd.ceiling = -1;
	parse->margin_l = -1;
	parse->margin_r = -1;
}

/// @brief Closes FD if it is bigger than 2
/// @param fd File descriptor to close
void	safe_close(int fd)
{
	if (fd > 2)
		close(fd);
}

/// @return length of STR until '\0' or C
int	len_until(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

/// @brief frees eveyrthing from the parse struct
void	cleanup_parse(t_parse *parse)
{
	free(parse->hd.no);
	free(parse->hd.so);
	free(parse->hd.we);
	free(parse->hd.ea);
	free_matrix((void **)parse->literal);
	free_matrix((void **)parse->padded);
}
