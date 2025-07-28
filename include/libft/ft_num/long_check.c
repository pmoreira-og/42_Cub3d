/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:50:52 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/09 14:13:34 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	long_overflow_check(char *arg, long *arg_n);

/// @brief Checks if ARG is a long and stores it in ARG_N
/// @param arg String to be checked
/// @param arg_n Where the number in ARG is to be stored
/// @return 1 if its a long, 0 if not
int	long_check(char *arg, long *arg_n)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(*arg))
		arg++;
	if (*arg == '-' || *arg == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		return (0);
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	while (arg[i] && ft_iswhitespace(arg[i]))
		i++;
	if (arg[i])
		return (0);
	if (long_overflow_check(arg, arg_n))
		return (0);
	return (1);
}

/// @brief Verifies if the number in ARG is within the range of a long
/// @param arg String to be checked
/// @param arg_n Where the number in ARG is to be stored
/// @return 1 if there's overflow, 0 when there isn't overflow
static int	long_overflow_check(char *arg, long *arg_n)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	if (*arg == '+' || *arg == '-')
		if (arg++ && *(arg - 1) == '-')
			sign = -1;
	while (ft_isdigit(*arg))
	{
		if (num > LONG_MAX / 10)
			return (1);
		if (num == LONG_MAX / 10 && ((sign == -1 && *arg - '0' > -(LONG_MIN
						% 10)) || (sign == 1 && *arg - '0' > LONG_MAX % 10)))
			return (1);
		num = num * 10 + (*arg - '0');
		arg++;
	}
	*arg_n = num * sign;
	return (0);
}
