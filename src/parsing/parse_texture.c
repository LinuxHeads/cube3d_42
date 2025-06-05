/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:49:10 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/06 01:33:09 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	parse_texture(t_game *game, char *line, int i, int type)
{
	char	**text;
	char	*ln;
	char	*path;

	text = ft_split(line, ' ');
	if (!text || !text[1])
	{
		ft_free_split(text);
		ln = ft_itoa(i);
		ft_exit_handler(game,
			(char *[]){"Error\nInvalid texture format on line ", ln, " .\n",
			NULL}, 1, ln);
	}
	path = ft_strtrim(text[1], " \t");
	if (!path)
	{
		ft_free_split(text);
		ft_exit_handler(game,
			(char *[]){"Error\nFailed to allocate memory for texture path.\
\non line: ", " file: ", __FILE__, ".\n", NULL}, 1, NULL);
	}
	game->map.texture[type - 1] = path;
	ft_free_split(text);
}
