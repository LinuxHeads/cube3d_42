/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:59:21 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/06 05:11:17 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// prints the games map, textures, and colors
void	print_game(t_game *game)
{
	size_t	i;
	size_t	j;

	printf("Map Content:\n");
	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
			printf("%c ", game->map.content[i][j]);
		printf("\n");
	}
	printf("Map Width: %zu\n", game->map.width);
	printf("Map Height: %zu\n", game->map.height);
	printf("Floor Color: R:%d G:%d B:%d\n", game->map.floor_color.r,
		game->map.floor_color.g, game->map.floor_color.b);
	printf("Ceiling Color: R:%d G:%d B:%d\n", game->map.ceiling_color.r,
		game->map.ceiling_color.g, game->map.ceiling_color.b);
	printf("Textures:\n");
	i = -1;
	while (++i < 4)
	{
		if (game->map.texture[i])
			printf("Texture %d: %s\n", i, game->map.texture[i]);
		else
			printf("Texture %d: NULL\n", i);
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	init(&game, argc, argv);
	parse(&game, argv[1]);
	print_game(&game);
	start_game(&game);
	ft_exit_handler(&game, (char *[]){"Game exited successfully.\n", NULL}, 0,
		NULL);
	return (0);
}
