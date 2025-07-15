/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:37:13 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/09 17:10:59 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	int	cnt;

	if (!str)
		str = "(null)";
	cnt = 0;
	while (*str)
	{
		write(1, &*str++, 1);
		cnt++;
	}
	return (cnt);
}

int	ft_prtnb_base(long nbr, char *base, int len)
{
	int	cnt;
	int	mod;

	cnt = 0;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
		cnt++;
	}
	if (nbr >= len)
		cnt += ft_prtnb_base(nbr / len, base, len);
	mod = nbr % len;
	write(1, &base[mod], 1);
	cnt++;
	return (cnt);
}

int	ft_printptr(unsigned long p, int flag)
{
	int	cnt;
	int	mod;

	cnt = 0;
	if (!p)
		return (ft_printstr("(nil)"));
	if (flag)
		cnt += write(1, "0x", 2);
	if (p >= 16)
		cnt += ft_printptr(p / 16, 0);
	mod = p % 16;
	cnt += write(1, &"0123456789abcdef"[mod], 1);
	return (cnt);
}
