/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:43:16 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/06 06:53:57 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void parse_map_line(t_game *game, char *line)
{
    char    *trimmed;
    t_list *temp;

    trimmed = ft_strtrim(line, "\n");// will probably just put \0 instead of \n
    if (!trimmed)
    {
        char *ln =  ft_itoa(__LINE__);
        ft_exit_handler(game, (char *[]){"Error\nFailed to allocate memory for line.\non line: ", ln ," file: ", __FILE__ , ".\n", NULL}, 1, ln);
    }
    temp = ft_lstnew(trimmed);
    if (!temp)
    {
        free(trimmed);
        char *ln =  ft_itoa(__LINE__);
        ft_exit_handler(game, (char *[]){"Error\nFailed to allocate memory for line.\non line: ", ln," file: ", __FILE__ , ".\n", NULL}, 1, ln);
    }
    game->map.height++;
    ft_lstadd_back(&game->map.buffer, temp);
}

// char *combine_line(char **line)
// {
//     char    *combined;
//     int     i;
//     int     len;
//     char *temp;

    
//     len = 0;
//     i = 0;
//     while (line[i])
//         len += ft_strlen(line[i++]) + 1;
//     combined = ft_strdup("");
//     if (!combined)
//     {
//         ft_putendl_fd("Error: Failed to allocate memory.", 2);
//         // use the exit handler
//         exit (1);
//     }
//     i = 0;
//     while (line[i])
//     {
//         temp = ft_strjoin(combined, line[i]);
//         if (!temp)
//         {
//             free(combined);
//             ft_putendl_fd("Error: Failed to allocate memory.", 2);
//             // use the exit handler
//             exit (1);
//         }
//         free(combined);
//         combined = temp;
//     }
//     return (combined);
// }
