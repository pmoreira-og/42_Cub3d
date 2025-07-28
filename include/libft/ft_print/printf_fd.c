/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:47:25 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/09 17:10:57 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	print_distribute_fd(const char *input, va_list args, int fd);

int	printf_fd(int fd, const char *input, ...)
{
	va_list	args;
	int		cnt;

	va_start(args, input);
	cnt = 0;
	while (*input)
	{
		if (*input == '%')
			cnt += print_distribute_fd(++input, args, fd);
		else
		{
			write(fd, &*input, 1);
			cnt++;
		}
		input++;
	}
	va_end(args);
	return (cnt);
}

static int	print_distribute_fd(const char *input, va_list args, int fd)
{
	int	cnt;

	if (*input == 'c')
		cnt = printchar_fd(va_arg(args, int), fd);
	if (*input == 's')
		cnt = printstr_fd(va_arg(args, char *), fd);
	if (*input == 'p')
		cnt = printptr_fd(va_arg(args, unsigned long), 1, fd);
	if (*input == 'd' || *input == 'i')
		cnt = prtnb_base_fd(va_arg(args, int), "0123456789", 10, fd);
	if (*input == 'u')
		cnt = prtnb_base_fd(va_arg(args, unsigned int), "0123456789", 10,
				fd);
	if (*input == 'x')
		cnt = prtnb_base_fd(va_arg(args, unsigned int), "0123456789abcdef",
				16, fd);
	if (*input == 'X')
		cnt = prtnb_base_fd(va_arg(args, unsigned int), "0123456789ABCDEF",
				16, fd);
	if (*input == '%')
		cnt = printchar_fd('%', fd);
	return (cnt);
}
