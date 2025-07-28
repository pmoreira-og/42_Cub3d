/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:46:02 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/09 14:11:09 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_next_line(int fd)
{
	int			len_read;
	static char	buff[BUFFER_SIZE + 1];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (ft_buffzero(buff, BUFFER_SIZE));
	line = ft_add_line_chunck(NULL, buff);
	if (!line)
		return (NULL);
	ft_buffrealign(buff);
	len_read = 1;
	while (!(ft_withnewline(line)))
	{
		len_read = read(fd, buff, BUFFER_SIZE);
		if (len_read <= 0)
			break ;
		line = ft_add_line_chunck(line, buff);
		if (!line)
			return (NULL);
		ft_buffrealign(buff);
	}
	if (!line[0] || len_read < 0)
		return (free(line), NULL);
	return (line);
}
