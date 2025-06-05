/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:43:16 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/06 01:16:12 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// I used AI here
void fill_map(t_game *game)
{
    size_t j;
    t_list *temp;
    size_t max_width;
    size_t line_len;
    t_list *width_check;
    
    if (game->map.height == 0) 
        ft_exit_handler(game, (char *[]){"Error\nNo map data found.\n", NULL}, 1, NULL);
    game->map.content = malloc(sizeof(char *) * (game->map.height + 1));
    if (!game->map.content)
        ft_exit_handler(game, (char *[]){"Error\nFailed to allocate memory for map content.\non line: ", " file: ", __FILE__ , ".\n", NULL}, 1, NULL);
    game->map.content[game->map.height] = NULL;
    temp = game->map.buffer;
    j = 0;
    max_width = 0;
    width_check = game->map.buffer;
    while (width_check)
    {
        line_len = ft_strlen(width_check->content);
        if (line_len > max_width)
            max_width = line_len;
        width_check = width_check->next;
    }
    game->map.width = max_width;
    while (temp && j < game->map.height)
    {
        line_len = ft_strlen(temp->content);
        game->map.content[j] = malloc(game->map.width + 1);
        if (!game->map.content[j])
            ft_exit_handler(game, (char *[]){"Error\nFailed to allocate memory for map line.\non line: ", " file: ", __FILE__ , ".\n", NULL}, 1, NULL);
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

void parse_map_line(t_game *game, char *line)
{
    char    *trimmed;
    t_list  *temp;
    char    *content_copy;
    
    trimmed = ft_strtrim(line, "\n\r");
    if (!trimmed)
        ft_exit_handler(game, (char *[]){"Error\nFailed to allocate memory for line.\non line: ", " file: ", __FILE__ , ".\n", NULL}, 1, NULL);
    content_copy = ft_strdup(trimmed);
    if (!content_copy)
        ft_exit_handler(game, (char *[]){"Error\nFailed to duplicate map line.\non line: ", " file: ", __FILE__ , ".\n", NULL}, 1, trimmed);
    temp = ft_lstnew(content_copy);
    if (!temp)
    {
        free(content_copy);
        ft_exit_handler(game, (char *[]){"Error\nFailed to allocate memory for line.\non line: ", " file: ", __FILE__ , ".\n", NULL}, 1, trimmed);
    }
    free(trimmed);
    game->map.height++;
    ft_lstadd_back(&game->map.buffer, temp);
}
