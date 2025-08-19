#include "../../include/cub3d.h"

/// @brief Closes FD if it is bigger than 2
/// @param fd File descriptor to close
void	safe_close(int fd)
{
	if (fd > 2)
		close(fd);
}

int	len_until(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	printf("len: %d\n", i);
	return (i);
}

void	cleanup_parse(t_parse *parse)
{
	free(parse->tx.SO);
	free(parse->tx.NO);
	free(parse->tx.WE);
	free(parse->tx.EA);
	free_matrix((void **)parse->literal);
	free_matrix((void **)parse->padded);
}
