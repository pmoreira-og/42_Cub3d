/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:27:12 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/09 14:11:09 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	strlen;
	size_t	size;
	char	*substring;

	if (s == NULL)
		return (0);
	strlen = ft_strlen(s);
	if (start >= strlen)
		return (ft_strdup(""));
	if (strlen - start < len)
		size = strlen - start;
	else
		size = len;
	substring = malloc((size + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	i = 0;
	while (s[start + i] && i < size)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = 0;
	return (substring);
}
