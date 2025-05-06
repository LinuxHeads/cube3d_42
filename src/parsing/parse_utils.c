/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:41:25 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/06 02:43:01 by abdsalah         ###   ########.fr       */
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
    if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0 ||
        ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
        return (1);
    else if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
        return (2);
    else if (line[0] == '1' || line[0] == ' ')
        return (3);
    return (0);
}
