/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:31:39 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/09 14:11:09 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_intlen(long n);

char	*ft_itoa(int n)
{
	int		i;
	long	num;
	char	*number;

	num = n;
	i = ft_intlen(num) - 1;
	number = malloc((i + 2) * sizeof(char));
	if (number == NULL)
		return (NULL);
	if (num < 0)
	{
		number[0] = '-';
		num = -num;
	}
	number[i + 1] = '\0';
	while (num > 9)
	{
		number[i--] = (num % 10) + 48;
		num /= 10;
	}
	number[i] = num + 48;
	return (number);
}

static int	ft_intlen(long n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n >= 1)
	{
		n /= 10;
		i++;
	}
	return (i);
}
