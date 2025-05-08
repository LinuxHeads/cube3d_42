/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:41:25 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/08 21:41:04 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
    int type = 0;
    
    if (!line || !*line)
        return 0;
    
    trimmed = ft_strtrim(line, " \n\r\t");
    if (!trimmed)
        return 0;
    if ((trimmed[0] == 'N' && trimmed[1] == 'O' && (trimmed[2] == ' ' || trimmed[2] == '\t')) ||
        (trimmed[0] == 'S' && trimmed[1] == 'O' && (trimmed[2] == ' ' || trimmed[2] == '\t')) ||
        (trimmed[0] == 'W' && trimmed[1] == 'E' && (trimmed[2] == ' ' || trimmed[2] == '\t')) ||
        (trimmed[0] == 'E' && trimmed[1] == 'A' && (trimmed[2] == ' ' || trimmed[2] == '\t')))
        type = 1;
    else if ((trimmed[0] == 'F' && (trimmed[1] == ' ' || trimmed[1] == '\t')) ||
             (trimmed[0] == 'C' && (trimmed[1] == ' ' || trimmed[1] == '\t')))
        type = 2;
    else if (trimmed[0] == '1' || trimmed[0] == '0' || trimmed[0] == ' ')
        type = 3;
    
    free(trimmed);
    return type;
}