/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:19:49 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/22 03:07:27 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int check_content(t_game *game)
{
    size_t i;
    size_t j;
    bool player_found;
    
    i = 0;
    player_found = false;
    while (i < game->map.height)
    {
        j = 0;
        while (j < ft_strlen(game->map.content[i]))
        {
            if (ft_strchr(" 01", game->map.content[i][j]))
            {
                if (game->map.content[i][j] == ' ')
                    game->map.content[i][j] = '0';
            }
            else if (ft_strchr("NSEW", game->map.content[i][j]))
            {
                if (player_found)
                    return (1);
                player_found = true;
                game->player.pos.x = j;
                game->player.pos.y = i;
                game->player.dir = game->map.content[i][j];
                game->map.content[i][j] = '1';
            }
            else
                return (1);
            j++;
        }
        i++;
    }
    if (!player_found)
        return (1);
    printf("Player found at (%lf, %lf)\n", game->player.pos.x, game->player.pos.y);
    return (0);
}

static int  flood_fill(char **map, int row, int col, t_game *game)
{
    size_t  max_cols;

    if (row < 0 || col < 0 || row >= (int)game->map.height)
        return (1);
    max_cols = ft_strlen(map[row]);
    if (col >= (int)max_cols)
        return (1);
    if (map[row][col] == '1' || map[row][col] == 'F')
        return (0);
    map[row][col] = 'F';
    if (flood_fill(map, row + 1, col, game) ||
        flood_fill(map, row - 1, col, game) ||
        flood_fill(map, row, col + 1, game) ||
        flood_fill(map, row, col - 1, game))
        return (1);
    return (0);
}

int     check_walls(t_game *game)
{
    char **map_copy;
    int ret;
    
    map_copy = dup_map(game);
    if (!map_copy)
        return (1);
    ret = flood_fill(map_copy, game->player.pos.x, game->player.pos.y, game);
    printf("Flood fill result: %d\n", ret);
    ft_free_split(map_copy);
    return (ret);
}

int    check_map(t_game *game)
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