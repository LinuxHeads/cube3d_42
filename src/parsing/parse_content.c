/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:43:16 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/08 21:27:36 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void parse_map_line(t_game *game, char *line)
{
    char    *trimmed;
    t_list  *temp;
    
    // Remove trailing newline but preserve spaces for map layout
    trimmed = ft_strtrim(line, "\n\r");
    if (!trimmed)
    {
        char *ln = ft_itoa(__LINE__);
        ft_exit_handler(game, (char *[]){"Error\nFailed to allocate memory for line.\non line: ", ln, " file: ", __FILE__ , ".\n", NULL}, 1, ln);
    }
    
    // Create a new list node with a copy of the trimmed string
    char *content_copy = ft_strdup(trimmed);
    if (!content_copy) {
        free(trimmed);
        char *ln = ft_itoa(__LINE__);
        ft_exit_handler(game, (char *[]){"Error\nFailed to duplicate map line.\non line: ", ln, " file: ", __FILE__ , ".\n", NULL}, 1, ln);
    }
    
    temp = ft_lstnew(content_copy);
    if (!temp)
    {
        free(content_copy);
        free(trimmed);
        char *ln = ft_itoa(__LINE__);
        ft_exit_handler(game, (char *[]){"Error\nFailed to allocate memory for line.\non line: ", ln, " file: ", __FILE__ , ".\n", NULL}, 1, ln);
    }
    
    free(trimmed); // We no longer need this as we've copied it
    game->map.height++;
    ft_lstadd_back(&game->map.buffer, temp);
}