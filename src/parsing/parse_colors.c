/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:47:28 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/13 05:41:47 by abdsalah         ###   ########.fr       */
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

int parse_rgb(char **text, t_rgb *rgb)
{
    int     i;
    char    *cmp;
    int     value;

    i = 0;
    while (i < 3)
    {
        cmp = ft_strtrim(text[i], " \tFC\n");
        if (!cmp)
            return (1);
        if (is_rgb(cmp))
        {
            value = ft_atoi(cmp);
            if (i == 0)
                rgb->r = value;
            if (i == 1)
                rgb->g = value;
            if (i == 2)
                rgb->b = value;
        }
        else
        {
            free(cmp);
            return (1);
        }
        free(cmp);
        i++;
    }
    return (0);
}

void parse_color(t_game *game, char *line)
{
    char    **text;
    t_rgb   rgb;

    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 0;
    text = ft_split(line, ',');
    if (!text || !text[0] || !text[1])
    {
        char *ln = ft_itoa(__LINE__);
        if (text) ft_free_split(text);
        ft_exit_handler(game, (char *[]){"Error: Invalid color format on line: ", ln, " file: ", __FILE__ , " .", NULL}, 1, ln);
    }
    if (parse_rgb(text, &rgb))
    {
        char *ln = ft_itoa(__LINE__);
        if (text) ft_free_split(text);
        ft_exit_handler(game, (char *[]){"Error: Invalid color format on line: ", ln, " file: ", __FILE__ , " .", NULL}, 1, ln);
    }
    if (ft_strncmp(text[0], "F", 1) == 0)
    {
        game->map.floor_color = rgb;
        printf("rgb %d %d %d\n", rgb.r, rgb.g, rgb.b);
    }
    else if (ft_strncmp(text[0], "C", 1) == 0)
    {
        game->map.ceiling_color = rgb;
        printf("rgb %d %d %d\n", rgb.r, rgb.g, rgb.b);
    }
    ft_free_split(text);
}
