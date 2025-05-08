/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:47:28 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/08 21:40:05 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool is_rgb(char *rgb)
{
    if (ft_strlen(rgb) == 0 || ft_strlen(rgb) > 3)
        return (false);
    if (!ft_isnumber(rgb))
        return (false);
    if (ft_atoi(rgb) < 0 || ft_atoi(rgb) > 255)
        return (false);
    return (true);
}

t_rgb parse_rgb(t_game *game, char *colors, char** text)
{
    t_rgb   rgb;
    char    **split;
    int     count;
    char *trimmed_colors;
    int i;
    int value;
    
    count = 0;
    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 0;
    trimmed_colors = ft_strtrim(colors, " \n\r\t");
    if (!trimmed_colors) 
    {
        ft_free_split(text);
        ft_exit_handler(game, (char *[]){"Error: Memory allocation failed.", NULL}, 1, NULL);
    }
    split = ft_split(trimmed_colors, ',');
    free(trimmed_colors);
    if (!split)
    {
        ft_free_split(text);
        ft_exit_handler(game, (char *[]){"Error: Failed to parse RGB values.", NULL}, 1, NULL);
    }
    while (split[count])
        count++;
    if (count != 3)
    {
        ft_free_split(split);
        ft_free_split(text);
        ft_exit_handler(game, (char *[]){"Error: RGB must have exactly 3 values.", NULL}, 1, NULL);
    }
    i = 0;
    while( i < 3)
    {
        char *trimmed_component = ft_strtrim(split[i], " \n\r\t");
        if (!trimmed_component)
        {
            ft_free_split(split);
            ft_free_split(text);
            ft_exit_handler(game, (char *[]){"Error: Memory allocation failed.", NULL}, 1, NULL);
        }
        if (!is_rgb(trimmed_component))
        {
            free(trimmed_component);
            ft_free_split(split);
            ft_free_split(text);
            ft_exit_handler(game, (char *[]){"Error: Invalid RGB value.", NULL}, 1, NULL);
        }
        free(trimmed_component);
        value = ft_atoi(split[i]);
        if (i == 0) 
            rgb.r = value;
        else if (i == 1) 
            rgb.g = value;
        else 
            rgb.b = value;
        i++;
    }

    ft_free_split(split);
    return (rgb);
}

void parse_color(t_game *game, char *line)
{
    char    **text;
    t_rgb   rgb;

    text = ft_split(line, ' ');
    if (!text || !text[0] || !text[1])
    {
        char *ln = ft_itoa(__LINE__);
        if (text) ft_free_split(text);
        ft_exit_handler(game, (char *[]){"Error: Invalid color format on line: ", ln, " file: ", __FILE__ , " .", NULL}, 1, ln);
    }
    rgb = parse_rgb(game, text[1], text);
    if (ft_strcmp(text[0], "F") == 0)
        game->map.floor_color = rgb;
    else if (ft_strcmp(text[0], "C") == 0)
        game->map.ceiling_color = rgb;
    else {
        ft_free_split(text);
        ft_exit_handler(game, (char *[]){"Error: Invalid color identifier (must be F or C).", NULL}, 1, NULL);
    }
    ft_free_split(text);
}
