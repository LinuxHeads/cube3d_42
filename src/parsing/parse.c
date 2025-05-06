/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:13:34 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/06 06:52:36 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void    read_and_store_line(t_game *game)
{
    char    *line;
    int     i;

    i = 0;
    while (1)
    {
        line = get_next_line(game->fd);
        if (!line)
            break ;
        if (line[0] == '\n')
        {
            free(line);
            continue ;
        }
        if (line_type(line) == 1)
            parse_texture(game, line, i);
        else if (line_type(line) == 2)
            parse_color(game, line);
        else if (line_type(line) == 3)
            parse_map_line(game, line);
        else
            ft_exit_handler(game, (char *[]){"Error\nInvalid line format on line ", ft_itoa(i), " .\n", NULL}, 1, line);
        free(line);
        i++;
    }
}

void fill_map(t_game *game)
{
    size_t j;

    game->map.content = malloc(sizeof(char *) * (game->map.height + 1));
    if (!game->map.content)
    {
        char *ln =  ft_itoa(__LINE__);
        ft_exit_handler(game, (char *[]){"Error\nFailed to allocate memory for map content.\non line: ", ln, " file: ", __FILE__ , ".\n", NULL}, 1, ln);
    }
    game->map.content[game->map.height] = NULL;
    t_list *temp = game->map.buffer;
    j = 0;
    while (temp)
    {
        game->map.content[j] = ft_strdup(temp->content);
        if (!game->map.content[j])
        {
            char *ln =  ft_itoa(__LINE__);
            ft_exit_handler(game, (char *[]){"Error\nFailed to allocate memory for map content.\non line: ", ln, " file: ", __FILE__ , ".\n", NULL}, 1, ln);
        }
        temp = temp->next;
        j++;
    }
    ft_lstclear(&game->map.buffer, free);
    game->map.width = ft_strlen(game->map.content[0]);
    while (j < game->map.height)
    {
        if (ft_strlen(game->map.content[j]) != game->map.width)
            ft_exit_handler(game, (char *[]){"Error\nMap lines are not of equal length.\n", NULL}, 1, NULL);
        j++;
    }
    close(game->fd);
    game->fd = -1;
    game->map.buffer = NULL;
}

void    parse_map(t_game *game)
{
    read_and_store_line(game);
    fill_map(game);
}

void    parse(t_game *game, char *file)
{
    setup_input_file(game, file);
    parse_map(game);
}