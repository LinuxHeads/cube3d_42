/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:19:49 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/14 04:01:02 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	check_chars(t_game *game, size_t i, size_t j, bool *player_found)
// needs testing
{
	if (ft_strchr(" 01", game->map.content[i][j]))
	{
		if (game->map.content[i][j] == ' ')
			game->map.content[i][j] = '0';
	}
	else if (ft_strchr("NSEW", game->map.content[i][j]))
	{
		if (*player_found)
			return (1);
		*player_found = true;
		game->player.pos.x = j;
		game->player.pos.y = i;
		game->player.dir = game->map.content[i][j];
		game->map.content[i][j] = '0';
	}
	else
		return (1);
	return (0);
}

static int	check_content(t_game *game)
{
	size_t	i;
	size_t	j;
	bool	player_found;

	i = 0;
	player_found = false;
	while (i < game->map.height)
	{
		j = 0;
		while (j < ft_strlen(game->map.content[i]))
		{
			if (check_chars(game, i, j, &player_found))
			{
				ft_putendl_fd("Error: Invalid character in map.", 2);
				return (1);
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		return (1);
	printf("Player found at (%lf, %lf)\n", game->player.pos.x,
		game->player.pos.y);
	return (0);
}

static int	check_walls(t_game *game)
{
	char	**map_copy;

	map_copy = dup_map(game);
	if (!map_copy)
		return (1);
	ft_free_split(map_copy);
	return (0);
}

int	check_map(t_game *game)
{
	if (check_content(game))
	{
		return (1);
	}
	if (check_walls(game))
	{
		return (1);
	}
	return (0);
}
