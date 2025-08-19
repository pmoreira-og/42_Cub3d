/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_allocer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:47:47 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/08/19 16:35:07 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief allocs a void ** that can be cast as any data type eg.: (char **)
/// @param row_size sifeof(data type *)
/// @param col_size sifeof(data type)
/// @param rows amount of rows
/// @param columns length of said rows
/// @return use ex.: char **twenty_words_with_three_chars[20][3]
/// , int **sudoku[9][9],
void	**matrix_allocer(long row_size, long col_size, size_t rows,
		size_t columns)
{
	void	**matrix;
	size_t	i;

	if (!row_size || !col_size || !rows || !columns || rows > SIZE_MAX
		/ row_size)
		return (NULL);
	matrix = malloc((rows + 1) * row_size);
	if (!matrix)
		return (NULL);
	i = -1;
	while (++i < rows)
	{
		matrix[i] = ft_calloc(columns + 1, col_size);
		if (!matrix[i])
			return (free_matrix_until(matrix, i), NULL);
	}
	matrix[i] = NULL;
	return (matrix);
}
