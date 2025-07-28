/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:51:42 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/09 14:09:22 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static bool	ft_stronly(char *str, const char *find);

/// @brief Checks if STR only contains characters from FIND
/// @param str String to be checked 
/// @param find String containing all "allowed" characters
/// @return true if it only contains chars in FIND, else false
static bool	ft_stronly(char *str, const char *find)
{
	int	i;

	if (!*str)
		return (false);
	i = -1;
	while (str[++i])
		if (!ft_strchr(find, str[i]))
			return (false);
	return (true);
}
