/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:13:34 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/22 03:03:59 by abdsalah         ###   ########.fr       */
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
        if(type != 7 && occurence_check(game, type))
        {
            free(line);
            return ;
        }
        if (type <= 4)
        {
            set_occurrence(game, type);   
            parse_texture(game, line, i, type);
        }
        else if (type <= 6)
        {
            if (!check_order(game, 1))
            {
                free(line);
                //raise error here  
                return ;
            }
            set_occurrence(game, type);
            parse_color(game, line);
        }
        else if (type == 7)
        {
            if (!check_order(game, 2))
            {
                free(line);
                //raise errwor here  
                return ;
            }
            set_occurrence(game, type);   
            parse_map_line(game, line);
        }
        else 
            exit (1);
            // ft_exit_handler(game, (char *[]){"Error\nInvalid line format", NULL} , 1,NULL);
        free(line);
        i++;
    }
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
    if (game->map.occurence != (MASK_TEXTURES | MASK_COLORS | (1 << 7)))
    {
        ft_exit_handler(game, (char *[]){"Error\nInvalid map format", NULL} , 1,NULL);
    }
    if (check_map(game))
    {
        printf("Error\nInvalid map format\n");
        // ft_exit_handler(game, (char *[]){"Error\nInvalid map format", NULL} , 1,NULL);
    }
}