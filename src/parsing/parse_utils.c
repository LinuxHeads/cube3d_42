/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:41:25 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/13 05:42:50 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void    set_occurrence(t_game *game, int type)
{
    game->map.occurence |= 1 << type;
}

int occurence_check(t_game *game, int type)
{
    if (1 << type & game->map.occurence)
    {
        return (1);
    }
    return (0);    
}

void    setup_input_file(t_game *game, char *file)
{
    game->fd = open(file, O_RDONLY);
    if (game->fd < 0)
    {
        ft_putendl_fd("Error: Failed to open file.", 2);
        // use the exit handler
        exit (1);
    }
}

int line_type(char *line)
{
    char *trimmed;
    int type;
    
    type = 0;
    if (!line || !*line)
        return (0);
    trimmed = ft_strtrim(line, " \n\r\t");
    if (!trimmed)
        return (0);
    if (trimmed[0] == 'N' && trimmed[1] == 'O' && ft_strchr(" \t", trimmed[2]))
        type = 1;
    if (trimmed[0] == 'S' && trimmed[1] == 'O' && ft_strchr(" \t", trimmed[2]))
        type = 2;
    if (trimmed[0] == 'W' && trimmed[1] == 'E' && ft_strchr(" \t", trimmed[2]))
        type = 3;
    if (trimmed[0] == 'E' && trimmed[1] == 'A' && ft_strchr(" \t", trimmed[2]))
        type = 4;
    if (trimmed[0] == 'F' && ft_strchr(" \t", trimmed[1]))
        type = 5;
    if (trimmed[0] == 'C' && ft_strchr(" \t", trimmed[1]))
        type = 6;
    if (trimmed[0] == '1' || trimmed[0] == '0' || trimmed[0] == ' ')
        type = 7;
    free(trimmed);
    return (type);
}
