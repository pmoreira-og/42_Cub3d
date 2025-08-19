#include "../../include/cub3d.h"

bool	get_map(t_game *game, char *input)
{
	t_parse	parse;

	// -- basic checks
	if (ft_strncmp(".cub", input + ft_strlen(input) - 4, 4))
		return (printf_fd(2, M_FEXT), false);
	init_parse_struct(&parse, input);
	// -- setups and validations
	if (!setup_for_extraction(&parse))
		return (false);
	if (!extract_header_info(&parse))
		return (cleanup_parse(&parse), false);
	if (!extract_map(&parse))
		return (cleanup_parse(&parse), false);
	// -- pass info to game struct
	(void)game;
	// -- free and close up parse
	cleanup_parse(&parse);
	return (true);
}

void	init_parse_struct(t_parse *parse, char *input)
{
	ft_bzero(parse, sizeof(t_parse));
	parse->path = input;
	parse->cl.floor = (t_rgb){-1, -1, -1};
	parse->cl.ceiling = (t_rgb){-1, -1, -1};
}
