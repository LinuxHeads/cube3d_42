/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:13:34 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/13 05:58:57 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void read_and_store_line(t_game *game)
{
    char    *line;
    int     i;
    int     type;

    i = 0;
    while (1)
    {
        line = get_next_line(game->fd);
        if (!line)
            break;
        
        if (line[0] == '\n' || line[0] == '\0')
        {
            free(line);
            continue;
        }
        type = line_type(line);
        if(type != 7 && occurence_check(game, type) )
        {
            return ;
        }
        if (type <= 4)
        {
            set_occurrence(game, type);   
            parse_texture(game, line, i, type);
        }
        else if (type <= 6)
        {
            set_occurrence(game, type);
            parse_color(game, line);
        }
        else if (type == 7)
        {
            set_occurrence(game, type);   
            parse_map_line(game, line);
        }
        else 
        {
            char *ln = ft_itoa(i + 1);
            ft_exit_handler(game, (char *[]){"Error\nInvalid line format on line ", ln, " .\n", NULL}, 1, ln);
        }
        free(line);
        i++;
    }
}

void fill_map(t_game *game)
{
    size_t j;

    if (game->map.height == 0) 
    {
        ft_exit_handler(game, (char *[]){"Error\nNo map data found.\n", NULL}, 1, NULL);
    }
    game->map.content = malloc(sizeof(char *) * (game->map.height + 1));
    if (!game->map.content)
    {
        char *ln = ft_itoa(__LINE__);
        ft_exit_handler(game, (char *[]){"Error\nFailed to allocate memory for map content.\non line: ", ln, " file: ", __FILE__ , ".\n", NULL}, 1, ln);
    }
    game->map.content[game->map.height] = NULL;
    t_list *temp = game->map.buffer;
    j = 0;
    size_t max_width = 0;
    t_list *width_check = game->map.buffer;
    while (width_check)
    {
        size_t line_len = ft_strlen(width_check->content);
        if (line_len > max_width)
            max_width = line_len;
        width_check = width_check->next;
    }
    game->map.width = max_width;
    while (temp && j < game->map.height)
    {
        size_t line_len = ft_strlen(temp->content);
        game->map.content[j] = malloc(game->map.width + 1);
        if (!game->map.content[j])
        {
            char *ln = ft_itoa(__LINE__);
            ft_exit_handler(game, (char *[]){"Error\nFailed to allocate memory for map line.\non line: ", ln, " file: ", __FILE__ , ".\n", NULL}, 1, ln);
        }
        ft_strlcpy(game->map.content[j], temp->content, line_len + 1);
        if (line_len < game->map.width)
        {
            ft_memset(game->map.content[j] + line_len, ' ', game->map.width - line_len);
            game->map.content[j][game->map.width] = '\0';
        }
        temp = temp->next;
        j++;
    }
    
    ft_lstclear(&game->map.buffer, free);
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