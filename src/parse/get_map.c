#include "../../include/cub3d.h"

# define M_FEXT	"incorrect file extention in inputed map path\n"
# define M_NOOP "couldn't open inputed map\n"
# define M_ERRO "Error\n"
# define M_LC "insuficient lines\n"

bool get_map(t_game	*game, char *input)
{
	int	fd;

	// -- basic checks
	if (ft_strncmp(".cub", input + ft_strlen(input) - 4, 4))
		return (printf_fd(2, M_FEXT), false);
	fd = open(input, O_RDONLY);
	if (fd < 3)
		return (printf_fd(2, M_NOOP), false);
	
	// -- reading the map, extracting and verifying it
	game->map = extract_map_from_file(input, fd);
	if (!game->map)
		return (false);

	
	return (true);
}

/// @brief Closes FD if it is bigger than 2
/// @param fd File descriptor to close
void	safe_close(int fd)
{
	if (fd > 2)
		close(fd);
}

char **extract_map_from_file(char *input, int fd)
{
	int lc;
	lc = get_file_line_count(fd);
	ft_printf("line_count: %d\n", lc);
	if (lc < 3)
		return (printf_fd(2, M_ERRO M_LC), NULL);
	fd = open(input, O_RDONLY);

	safe_close(fd);
	return (printf_fd(2, M_ERRO), NULL);
}

int	get_file_line_count(int fd)
{
	int 	lc;
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
