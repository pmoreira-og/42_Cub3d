/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:11:22 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/09/29 18:13:32 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	valid_color_format(char *code);
static bool	assign_color_code(char *code, int *type);

/// @brief gets color code from CODE and sees if its a valid color
/// @param cl header struct containig the colors
/// @param code full line with color identifier and code
/// @return true on success, false on failure
bool	extract_color(t_header *cl, char *code)
{
	int		i;
	int		color_len;
	char	color[12];
	int		*type;

	type = NULL;
	if (!ft_strncmp(code, "F ", 2))
		type = &cl->floor;
	else if (!ft_strncmp(code, "C ", 2))
		type = &cl->ceiling;
	if (*type != -1)
		return (printf_fd(2, M_ERRO M_REP), false);
	i = 2;
	while (code[i] == ' ')
		i++;
	color_len = len_until(&code[i], '\n');
	if (color_len < 5 || color_len > 11)
		return (printf_fd(2, M_ERRO M_COLF), false);
	ft_bzero(color, sizeof(color));
	ft_memcpy(color, &code[i], color_len);
	if (!valid_color_format(color))
		return (printf_fd(2, M_ERRO M_COLF), false);
	if (!assign_color_code(color, type))
		return (printf_fd(2, M_ERRO M_COLF), false);
	return (true);
}

/// @brief sees if CODE is in the [0-255],[0-255],[0-255] format
/// @return true when valid, false when invalid
static bool	valid_color_format(char *code)
{
	int	i;
	int	j;
	int	field;
	int	num_len;

	i = 0;
	field = -1;
	while (++field < 3)
	{
		j = -1;
		num_len = len_until(&code[i], ',');
		if (num_len < 1 || num_len > 3 || (field < 2 \
	&& code[i + num_len] != ',') || (field == 2 && code[i + num_len]))
			return (false);
		while (++j < num_len)
			if (!ft_isdigit(code[i + j]))
				return (false);
		i += num_len + 1;
	}
	return (true);
}

/// @brief converts CODE into an hex color number
/// @param code RGB string
/// @param type pointer to the floor or ceiling color
/// @return true on success, false on failure
static bool	assign_color_code(char *code, int *type)
{
	char	color[4];
	int		num_len;
	int		param;
	int		val;

	param = 1;
	*type = 0;
	while (*code)
	{
		ft_bzero(color, sizeof(color));
		num_len = len_until(code, ',');
		ft_memcpy(color, code, num_len);
		val = ft_atoi(color);
		if (val > 255)
			return (false);
		if (param == 1)
			*type |= (val << 16);
		else if (param == 2)
			*type |= (val << 8);
		else if (param == 3)
			*type |= (val);
		param++;
		code += num_len + 1;
	}
	return (true);
}
