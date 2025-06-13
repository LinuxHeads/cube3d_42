/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:49:10 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/12 07:31:55 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_textures(t_game *game)
{
	if (!game || !game->mlx)
		return (0);
	game->map.north_texture = mlx_load_png(game->map.texture[NO]);
	if (!game->map.north_texture)
		return (0);
	game->map.south_texture = mlx_load_png(game->map.texture[SO]);
	if (!game->map.south_texture)
		return (0);
	game->map.west_texture = mlx_load_png(game->map.texture[WE]);
	if (!game->map.west_texture)
		return (0);
	game->map.east_texture = mlx_load_png(game->map.texture[EA]);
	if (!game->map.east_texture)
		return (0);
	return (1);
}


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
	path = ft_strtrim(text[1], " \n\t");
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
