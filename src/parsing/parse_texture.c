/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:49:10 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/06 06:09:58 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void parse_texture(t_game *game, char *line, int i)
{
    char    **text;

    text = ft_split(line, ' ');
    if (!text || !text[1])
    {
       ft_exit_handler(game, (char *[]){"Error\nInvalid texture format on line ", ft_itoa(i), " .\n", NULL}, 1, line);
    }
    char *path = ft_strdup(text[1]);
    if (!path)
    {
        ft_free_split(text);
        char *ln =  ft_itoa(__LINE__);
        ft_exit_handler(game, (char *[]){"Error\nFailed to allocate memory for texture path.\non line: ", ln," file: ", __FILE__ , ".\n", NULL}, 1, ln);
    }
    if (ft_strcmp(text[0], "NO") == 0)
        game->map.texture[NO] = path;
    else if (ft_strcmp(text[0], "SO") == 0)
        game->map.texture[SO] = path;
    else if (ft_strcmp(text[0], "WE") == 0)
        game->map.texture[WE] = path;
    else if (ft_strcmp(text[0], "EA") == 0)
        game->map.texture[EA] = path;
    ft_free_split(text);
}
