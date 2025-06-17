/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:17:57 by msalim            #+#    #+#             */
/*   Updated: 2025/06/14 14:06:43 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.player_dir.x * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.player_dir.y * MOVE_SPEED;
	if (game->map.content[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
	if (game->map.content[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x - game->player.player_dir.x * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.player_dir.y * MOVE_SPEED;
	if (game->map.content[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
	if (game->map.content[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x - game->player.camera_plane.x * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.camera_plane.y * MOVE_SPEED;
	if (game->map.content[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
	if (game->map.content[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.camera_plane.x * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.camera_plane.y * MOVE_SPEED;
	if (game->map.content[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
	if (game->map.content[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
}
