/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_dup_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:35:58 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/09 16:38:14 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**matrix_dup_char(char **original_matrix)
{
	char	**dup;
	int		i;

	if (!original_matrix)
		return (NULL);
	dup = malloc((ft_matrixlen(original_matrix) + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	i = -1;
	while (original_matrix[++i])
	{
		dup[i] = ft_strdup(original_matrix[i]);
		if (!dup[i])
			return (free_matrix_until((void **)dup, i), NULL);
	}
	dup[i] = NULL;
	return (dup);
}
