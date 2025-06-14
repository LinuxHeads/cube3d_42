/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 04:07:51 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/14 10:20:27 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	flood_fill(char **map, int row, int col, t_game *game)
{
	size_t	max_cols;
	int		leak;

	if (row < 0 || row >= (int)game->map.height)
		return (1);
	max_cols = ft_strlen(map[row]);
	if (col < 0 || col >= (int)max_cols)
		return (1);
	if (map[row][col] == '1' || map[row][col] == 'F')
		return (0);
	map[row][col] = 'F';
	leak = 0;
	leak = flood_fill(map, row + 1, col, game) || flood_fill(map, row - 1, col,
			game) || flood_fill(map, row, col + 1, game) || flood_fill(map, row,
			col - 1, game);
	return (leak);
}

/**
 * @brief Check that every open cell '0' is enclosed by '1's.
 * Duplicate the map, flood-fill each zero-region once,
 * and detect any leaking region.
 */
int	check_walls(t_game *game)
{
	char	**map_copy;
	int		r;
	int		c;
	int		leak;

	map_copy = dup_map(game);
	if (!map_copy)
		return (1);
	leak = 0;
	r = -1;
	while (++r < (int)game->map.height && !leak)
	{
		c = 0;
		while (map_copy[r][c] && !leak)
		{
			if (map_copy[r][c] == '0')
			{
				if (flood_fill(map_copy, r, c, game))
					leak = 1;
			}
			c++;
		}
	}
	ft_free_split(map_copy);
	return (leak);
}
