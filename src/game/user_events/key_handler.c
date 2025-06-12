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

void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		else if (keydata.key == MLX_KEY_W)
			move_forward(game);
		else if (keydata.key == MLX_KEY_S)
			move_backward(game);
		else if (keydata.key == MLX_KEY_A)
			move_left(game);
		else if (keydata.key == MLX_KEY_D)
			move_right(game);
		else if (keydata.key == MLX_KEY_LEFT)
			rotate_left(game);
		else if (keydata.key == MLX_KEY_RIGHT)
			rotate_right(game);
	}
}
