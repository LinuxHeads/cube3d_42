/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:59:21 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/31 19:14:28 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void print_game(t_game *game)
{
    printf("Map Content:\n");
    for (size_t i = 0; i < game->map.height; i++)
    {
        for (size_t j = 0; j < game->map.width; j++)
        {
            printf("%c ", game->map.content[i][j]);
        }
        printf("\n");
    }
    printf("Map Width: %zu\n", game->map.width);
    printf("Map Height: %zu\n", game->map.height);
    printf("Floor Color: R:%d G:%d B:%d\n", game->map.floor_color.r, game->map.floor_color.g, game->map.floor_color.b);
    printf("Ceiling Color: R:%d G:%d B:%d\n", game->map.ceiling_color.r, game->map.ceiling_color.g, game->map.ceiling_color.b);
    printf("Textures:\n");
    for (int i = 0; i < 4; i++)
    {
        if (game->map.texture[i])
            printf("Texture %d: %s\n", i, game->map.texture[i]);
        else
            printf("Texture %d: NULL\n", i);
    }
}

int main(int argc, char **argv)
{
    t_game game;

    init(&game, argc, argv);
    parse(&game, argv[1]);
    print_game(&game);
    start_game(&game);
    ft_exit_handler(&game, (char *[]){"Game exited successfully.\n", NULL}, 0, NULL);
    return (0);
}