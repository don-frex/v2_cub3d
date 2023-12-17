/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:34:46 by asaber            #+#    #+#             */
/*   Updated: 2023/12/17 20:05:37 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	squar_draw(float x, float y, int color, mlx_image_t *image)
{
	int	i;
	int	j;

	i = 0;
	while (i < SQUIR_SIZE * g_info.minimap)
	{
		j = 0;
		while (j < SQUIR_SIZE * g_info.minimap)
		{
			mlx_put_pixel(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_floor_and_ceiling(double s_p, double e_p, double stripId)
{
	while (s_p >= 0)
	{
		mlx_put_pixel(g_info.image, stripId, s_p, ft_pixel(197, 255, 248, 255));
		s_p--;
	}
	while (e_p <= g_info.hight)
	{
		mlx_put_pixel(g_info.image, stripId, e_p, ft_pixel(245, 232, 199, 255));
		e_p++;
	}
}

void	draw_by_diriction(double stripId, double start_point, double end_point)
{
	while (start_point < end_point)
	{
		mlx_put_pixel(g_info.image, stripId, start_point, 
			ft_pixel(95, 15, 64, 255));
		start_point++;
	}
}

void	draw_walls(double stripId)
{
	double	start_point;
	double	end_point;

	g_info.distprojectplane = (g_info.wight / 2) / tan(g_info.fov_angle / 2);
	g_info.f_dist = g_info.f_dist * 
		cos(g_info.ray_angle - g_info.player.rotation_angle);
	g_info.wallstriphight = 
		SQUIR_SIZE / g_info.f_dist * g_info.distprojectplane;
	start_point = (g_info.hight / 2) - (g_info.wallstriphight / 2);
	end_point = (g_info.hight / 2) + (g_info.wallstriphight / 2);
	draw_floor_and_ceiling(start_point, end_point, stripId);
	if (start_point < 0)
		start_point = 0;
	if (end_point > g_info.hight)
		end_point = g_info.hight;
	draw_by_diriction(stripId, start_point, end_point);
}

void	draw_map(void *param)
{
	int	i;
	int	j;

	i = 0;
	(void)param;
	draw_player();
	while (g_info.map[i])
	{
		j = 0;
		while (g_info.map[i][j])
		{
			if (g_info.map[i][j] == '1')
				squar_draw(g_info.minimap * (j * SQUIR_SIZE), g_info.minimap * 
					(i * SQUIR_SIZE), 
					ft_pixel(255, 255, 255, 255), g_info.image);
			else if (g_info.map[i][j] == '0' || g_info.map[i][j] == 'N' 
				|| g_info.map[i][j] == 'S' || g_info.map[i][j] == 'W' 
				|| g_info.map[i][j] == 'E')
				squar_draw(g_info.minimap * (j * SQUIR_SIZE), g_info.minimap * 
					(i * SQUIR_SIZE), ft_pixel(0, 0, 0, 255), g_info.image);
			j++;
		}
		i++;
	}
	draw_ray_angel();
}
