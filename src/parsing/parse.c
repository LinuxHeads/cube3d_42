/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:13:34 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/14 10:10:46 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	evaluate_line(t_game *game, int type, char *line)
{
	if (type == 0)
		ft_exit_handler(game, (char *[]){"Error\ninvalid line format at line",
			NULL}, 1, line);
	if (type != 7 && occurence_check(game, type))
		ft_exit_handler(game, (char *[]){"Error\nDuplicated input detected.\n",
			NULL}, 1, line);
	else if (type <= 6)
	{
		set_occurrence(game, type);
		if (type <= 4)
			parse_texture(game, line, type);
		else
			parse_color(game, line);
	}
	else if (type == 7)
	{
		if (!check_order(game, 2))
			ft_exit_handler(game, (char *[]){"Error\nInvalid line format",
				NULL}, 1, line);
		set_occurrence(game, type);
		parse_map_line(game, line);
	}
	else
		ft_exit_handler(game, (char *[]){"Error\nInvalid line format", NULL}, 1,
			NULL);
}

void	read_and_store_line(t_game *game)
{
	char	*line;
	int		type;
	int		last_type;

	last_type = -1;
	while (1)
	{
		line = get_next_line(game->fd);
		if (!line)
			break ;
		if (line[0] == '\n' || line[0] == '\0')
		{
			if (last_type == 7)
				ft_exit_handler(game,
					(char *[]){"Error\nCan't have empty lines in map content\n",
					NULL}, 1, line);
			free(line);
			continue ;
		}
		type = line_type(line);
		evaluate_line(game, type, line);
		free(line);
		last_type = type;
	}
}

void	parse_map(t_game *game)
{
	read_and_store_line(game);
	fill_map(game);
}

void	parse(t_game *game, char *file)
{
	setup_input_file(game, file);
	parse_map(game);
	if (game->map.occurence != (MASK_TEXTURES | MASK_COLORS | (1 << 7)))
	{
		ft_exit_handler(game, (char *[]){"Error\nInvalid map format", NULL}, 1,
			NULL);
	}
	if (check_map(game))
	{
		ft_exit_handler(game, (char *[]){"Error\nInvalid map format.\n",
			NULL}, 1, NULL);
	}
}
