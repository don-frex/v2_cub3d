/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:53:32 by asaber            #+#    #+#             */
/*   Updated: 2023/12/16 21:56:41 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move(float x, float y)
{
	mlx_put_pixel(g_info.image, g_info.minimap * g_info.player.x, 
		g_info.minimap * g_info.player.y, ft_pixel(255, 0, 40, 255));
	mlx_put_pixel(g_info.image, g_info.minimap * x, 
		g_info.minimap * y, ft_pixel(255, 0, 40, 255));
	if (_x_y_to_check(y / SQUIR_SIZE, g_info.player.x / 
			SQUIR_SIZE, g_info.map))
		g_info.player.y = y;
	if (_x_y_to_check(g_info.player.y / SQUIR_SIZE, x / 
			SQUIR_SIZE, g_info.map))
		g_info.player.x = x;
}

void	mlx_moves(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		player_move(g_info.player.x + 
			cos(g_info.player.rotation_angle - M_PI / 2) * 
			g_info.player.move_speed, g_info.player.y + 
			sin(g_info.player.rotation_angle - M_PI / 2) * 
			g_info.player.move_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		player_move(g_info.player.x - 
			cos(g_info.player.rotation_angle) * 
			g_info.player.move_speed, g_info.player.y - 
			sin(g_info.player.rotation_angle) * 
			g_info.player.move_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		player_move(g_info.player.x - 
			cos(g_info.player.rotation_angle - M_PI / 2) * 
			g_info.player.move_speed, g_info.player.y - 
			sin(g_info.player.rotation_angle - M_PI / 2) * 
			g_info.player.move_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		player_move(g_info.player.x + 
			cos(g_info.player.rotation_angle) * 
			g_info.player.move_speed, g_info.player.y + 
			sin(g_info.player.rotation_angle) * g_info.player.move_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		g_info.player.rotation_angle -= 0.034;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		g_info.player.rotation_angle += 0.034;
}
