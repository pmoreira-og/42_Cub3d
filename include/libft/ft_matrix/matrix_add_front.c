/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_add_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:37:00 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/09 16:38:13 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**matrix_add_front(char *add, char **original)
{
	char	**new;
	int		i;

	if ((!add && !original) || !add)
		return (NULL);
	new = ft_calloc(ft_matrixlen(original) + 2, sizeof(char *));
	if (!new)
		return (NULL);
	new[0] = ft_strdup(add);
	if (!new[0])
		return (free(new), NULL);
	i = -1;
	while (original && original[++i])
		new[i + 1] = original[i];
	if (original)
		new[i + 1] = NULL;
	else
		new[1] = NULL;
	free(original);
	return (new);
}
