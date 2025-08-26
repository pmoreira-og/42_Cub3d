/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:44:12 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/08/19 16:59:42 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	matrix_print(char **matrix)
{
	int	i;
	int	j;

	i = -1;
	while (matrix[++i])
	{
		j = -1;
		while (matrix[i][++j])
			write(1, &matrix[i][j], 1);
		write(1, "|\n", 2);
	}
}
