/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:40:59 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/12 09:41:05 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.player_dir.x;
	old_plane_x = game->player.camera_plane.x;
	game->player.player_dir.x = game->player.player_dir.x * cos(ROT_SPEED)
		- game->player.player_dir.y * sin(ROT_SPEED);
	game->player.player_dir.y = old_dir_x * sin(ROT_SPEED)
		+ game->player.player_dir.y * cos(ROT_SPEED);
	game->player.camera_plane.x = game->player.camera_plane.x * cos(ROT_SPEED)
		- game->player.camera_plane.y * sin(ROT_SPEED);
	game->player.camera_plane.y = old_plane_x * sin(ROT_SPEED)
		+ game->player.camera_plane.y * cos(ROT_SPEED);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.player_dir.x;
	old_plane_x = game->player.camera_plane.x;
	game->player.player_dir.x = game->player.player_dir.x * cos(-ROT_SPEED)
		- game->player.player_dir.y * sin(-ROT_SPEED);
	game->player.player_dir.y = old_dir_x * sin(-ROT_SPEED)
		+ game->player.player_dir.y * cos(-ROT_SPEED);
	game->player.camera_plane.x = game->player.camera_plane.x * cos(-ROT_SPEED)
		- game->player.camera_plane.y * sin(-ROT_SPEED);
	game->player.camera_plane.y = old_plane_x * sin(-ROT_SPEED)
		+ game->player.camera_plane.y * cos(-ROT_SPEED);
}
