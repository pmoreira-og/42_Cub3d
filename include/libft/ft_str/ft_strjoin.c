/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:29:54 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/09 17:15:38 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	j = 0;
	string = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (string == NULL)
		return (0);
	while (s1[i] != 0)
	{
		string[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
	{
		string[i + j] = s2[j];
		j++;
	}
	string[i + j] = 0;
	return (string);
}
