/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:49:10 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/14 03:19:59 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	parse_texture(t_game *game, char *line, int type)
{
	char	**text;
	char	*path;

	text = ft_split(line, ' ');
	if (!text || !text[1])
	{
		ft_free_split(text);
		ft_exit_handler(game,
			(char *[]){"Error\nInvalid texture format.\n",
			NULL}, 1, NULL);
	}
	path = ft_strtrim(text[1], " \n\t");
	if (!path)
	{
		ft_free_split(text);
		ft_exit_handler(game,
			(char *[]){"Error\nFailed to allocate memory for texture path.\n",
				NULL}, 1, NULL);
	}
	game->map.texture[type - 1] = path;
	ft_free_split(text);
}
