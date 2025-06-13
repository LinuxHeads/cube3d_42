/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:40:33 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/12 09:40:45 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
void	handle_input(t_game *game)
{
	// Handle rotation
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game);
	
	// Handle movement
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game);
	
	// Handle exit
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

// Simplified keypress handler - only for immediate one-time actions if needed
/* /1* void	handle_keypress(mlx_key_data_t keydata, void *param) *1/ */
/* /1* { *1/ */
/* 	t_game	*game; */

/* 	game = (t_game *)param; */
	
/* 	// Only handle immediate actions that should happen once per press */
/* 	// ESC is now handled in handle_input() for consistency, but you could keep it here */
/* 	// if you prefer one-time press behavior over hold-to-exit */
/* 	if (keydata.action == MLX_PRESS) */
/* 	{ */
/* 		// Add any one-time press actions here if needed */
/* 		// For example: toggle fullscreen, pause game, etc. */
/* 	} */
/* } */

