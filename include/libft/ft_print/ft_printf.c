/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:58:25 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/09 14:11:09 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		cnt;

	va_start(args, input);
	cnt = 0;
	while (*input)
	{
		if (*input == '%')
			cnt += ft_ispercent(++input, args);
		else
		{
			write(1, &*input, 1);
			cnt++;
		}
		input++;
	}
	va_end(args);
	return (cnt);
}

int	ft_ispercent(const char *input, va_list args)
{
	int	cnt;

	if (*input == 'c')
		cnt = ft_printchar(va_arg(args, int));
	if (*input == 's')
		cnt = ft_printstr(va_arg(args, char *));
	if (*input == 'p')
		cnt = ft_printptr(va_arg(args, unsigned long), 1);
	if (*input == 'd' || *input == 'i')
		cnt = ft_prtnb_base(va_arg(args, int), "0123456789", 10);
	if (*input == 'u')
		cnt = ft_prtnb_base(va_arg(args, unsigned int), "0123456789", 10);
	if (*input == 'x')
		cnt = ft_prtnb_base(va_arg(args, unsigned int), "0123456789abcdef", 16);
	if (*input == 'X')
		cnt = ft_prtnb_base(va_arg(args, unsigned int), "0123456789ABCDEF", 16);
	if (*input == '%')
		cnt = ft_printchar('%');
	return (cnt);
}
