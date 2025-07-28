/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:29:57 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/09 17:15:25 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_trimbegin(char const *s1, char const *set);
static int	ft_trimend(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		begin;
	int		end;
	int		i;
	char	*trimmed;

	if (s1 == 0)
		return (NULL);
	begin = ft_trimbegin(s1, set);
	end = ft_trimend(s1, set);
	i = 0;
	trimmed = malloc((end - begin + 1) * sizeof(char));
	if (trimmed == NULL)
		return (0);
	while (s1[begin] && begin < end)
		trimmed[i++] = s1[begin++];
	trimmed[i] = 0;
	return (trimmed);
}

static int	ft_trimbegin(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i] != set[j] && set[j])
			j++;
		if (s1[i] == set[j])
			i++;
		else
			return (i);
	}
	return (0);
}

static int	ft_trimend(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
		i++;
	i--;
	while (i >= 0)
	{
		j = 0;
		while (s1[i] != set[j] && set[j])
			j++;
		if (s1[i] == set[j])
			i--;
		else
			return (++i);
	}
	return (0);
}
