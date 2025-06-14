/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 03:24:13 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/14 03:36:29 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	free_map_textures(t_game *game)
{
	size_t	i;

	i = -1;
	while (++i < 4)
	{
		if (game->map.texture[i])
		{
			free(game->map.texture[i]);
			game->map.texture[i] = NULL;
		}
	}
}

static void	free_map_content(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->map.height)
	{
		if (game->map.content[i])
			free(game->map.content[i]);
		else
			break ;
		i++;
	}
}

void	free_map(t_game *game)
{
	if (game->map.height && game->map.width)
	{
		free_map_content(game);
	}
	if (game->map.content)
		free(game->map.content);
	game->map.content = NULL;
	if (game->map.buffer)
		ft_lstclear(&game->map.buffer, free);
	game->map.buffer = NULL;
	free_map_textures(game);
	if (game->fd > 0)
		close(game->fd);
	game->fd = -1;
}
