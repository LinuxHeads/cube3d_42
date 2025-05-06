/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:47:28 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/06 06:09:07 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool is_rgb(char **split)
{
    int i;

    i = 0;
    while (split[i])
    {
        if (ft_strlen(split[i]) == 0 || ft_strlen(split[i]) > 3)
            return (false);
        if (!ft_isnumber(split[i]))
            return (false);
        if (ft_atoi(split[i]) < 0 || ft_atoi(split[i]) > 255)
            return (false);
        i++;
    }
    return (true);
}

t_rgb   parse_rgb(t_game *game, char *colors, char** text)
{
    t_rgb   rgb;
    char    **split;

    split = ft_split(colors, ',');
    if (!split || !split[0] || !split[1] || !split[2])
    {
        ft_free_split(text);
        ft_exit_handler(game, (char *[]){"Error: Invalid RGB format.", NULL}, 1, NULL);
    }
    if (!is_rgb(split))
    {
        ft_free_split(split);
        ft_free_split(text);
        ft_exit_handler(game, (char *[]){"Error: Invalid RGB values.", NULL}, 1, NULL);
    }
    rgb.r = ft_atoi(split[0]);
    rgb.g = ft_atoi(split[1]);
    rgb.b = ft_atoi(split[2]);
    ft_free_split(split);
    return (rgb);
}

void    parse_color(t_game *game, char *line)
{

    char    **text;
    t_rgb   rgb;

    text = ft_split(line, ' ');
    if (!text)
    {
        char *ln =  ft_itoa(__LINE__);
        ft_exit_handler(game, (char *[]){"Error: Failed to split line on line: ", ln, " file: ", __FILE__ , " .", NULL}, 1, ln);
    }
    rgb = parse_rgb(game, text[1], text);
    if (ft_strcmp(text[0], "F") == 0)
        game->map.floor_color = rgb;
    else if (ft_strcmp(text[0], "C") == 0)
        game->map.ceiling_color = rgb;
    ft_free_split(text);
}
