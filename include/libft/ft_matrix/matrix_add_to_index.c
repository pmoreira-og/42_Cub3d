/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_add_to_index.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:51:32 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/09 16:38:11 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief Adds string ADD to the MATRIX on index IDX
/// @param matrix Char ** to be added to
/// @param add String to be added to MATRIX
/// @param idx Index for where to add
/// @param len Length of MATRIX
/// @return New MATRIX with added ADD, or NULL on malloc failure
char	**matrix_add_to_index(char **matrix, char *add, size_t idx, size_t len)
{
	char	**new;
	int		i;
	int		j;

	if (!add || !matrix || len < 1 || idx > len + 1)
		return (matrix);
	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
		return (NULL);
	i = -1;
	j = -1;
	while (++i <= (int)len)
	{
		if (i == (int)idx)
		{
			new[++j] = ft_strdup(add);
			if (!new[j])
				return (free(new), NULL);
		}
		new[++j] = matrix[i];
	}
	free(matrix);
	return (new);
}
