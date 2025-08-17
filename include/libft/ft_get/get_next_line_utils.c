/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:45:59 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/08/17 18:12:29 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_add_line_chunck(char *start, char *chunck)
{
	int		i;
	int		j;
	char	*line;

	if (!start)
	{
		start = malloc(1 * sizeof(char));
		start[0] = '\0';
	}
	line = malloc((ft_linelen(start) + ft_linelen(chunck) + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = -1;
	while (start[++i])
		line[i] = start[i];
	j = 0;
	if (chunck[j])
		line[i++] = chunck[j++];
	while (chunck[j] && chunck[j - 1] != '\n')
		line[i++] = chunck[j++];
	line[i] = '\0';
	return (free(start), line);
}

void	ft_buffrealign(char *buff)
{
	int	i;
	int	j;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	j = 0;
	if (buff[i] == '\n')
		while (buff[++i] && i < BUFFER_SIZE)
			buff[j++] = buff[i];
	ft_buffzero(&buff[j], BUFFER_SIZE - j);
}

int	ft_withnewline(char *line)
{
	int	len;

	len = ft_linelen(line);
	while (len >= 0)
	{
		if (line[len] == '\n')
			return (1);
		len--;
	}
	return (0);
}

int	ft_linelen(char *str)
{
	int	i;

	i = 0;
	if (str[i])
		i++;
	while (str[i] && str[i - 1] != '\n')
		i++;
	return (i);
}

void	*ft_buffzero(char *buff, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		buff[i++] = 0;
	return (NULL);
}
