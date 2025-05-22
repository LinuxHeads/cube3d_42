/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:41:23 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/22 01:47:04 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


// dups the map content
char    **dup_map(t_game *game)
{
    char **map_copy;
    size_t i;
    size_t j;
    
    i = 0;
    j = 0;
    map_copy = ft_calloc(sizeof(char *), game->map.height + 1);
    if (!map_copy)
        return (NULL);
    while (i < game->map.height)
    {
        map_copy[i] = ft_strdup(game->map.content[i]);
        if (!map_copy[i])
        {
            while (j < i)
                free(map_copy[j++]);
            free(map_copy);
            return (NULL);
        }
        i++;
    }
    map_copy[i] = NULL;
    return (map_copy);
}