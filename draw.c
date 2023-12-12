/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:34:46 by asaber            #+#    #+#             */
/*   Updated: 2023/12/12 22:26:13 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	squar_draw(float x, float y, float size_square, int color, mlx_image_t *image)
{
	int i;
	int j;

	i = 0;
	while (i < size_square)
	{
		j = 0;
		while (j < size_square)
		{
			mlx_put_pixel(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

// drawing player

void	draw_player(void)
{
	int i;
	int j;

	i = 0;
	while (i < g_info.player.raduis)
	{
		j = 0;
		while (j < g_info.player.raduis)
		{
			mlx_put_pixel(g_info.image, g_info.minimap * g_info.player.x + i, g_info.minimap *  g_info.player.y + j, ft_pixel(123, 102, 255, 255));
			j++;
		}
		i++;
	}
}

//drwaing floor and ceiling

void	draw_floor_and_ceiling(double start_point, double end_point, double stripId)
{
	while (start_point >= 0)
	{
		mlx_put_pixel(g_info.image, stripId, start_point, ft_pixel(197, 255, 248, 255));
		start_point--;
	}
	while (end_point <= g_info.HIGHT)
	{
		mlx_put_pixel(g_info.image, stripId, end_point, ft_pixel(245, 232, 199, 255));
		end_point++;
	}
}

void	draw_walls(double stripId)
{
	double wallStripHight;
	double start_point;
	double end_point;
	g_info.distProjectPlane = (g_info.WIGHT / 2) / tan(g_info.fov_angle / 2);
	g_info.wallStripHight = squire_size / g_info.f_dist * g_info.distProjectPlane;
	
	start_point = (g_info.HIGHT / 2) - (g_info.wallStripHight / 2);
	end_point = (g_info.HIGHT / 2) + (g_info.wallStripHight / 2);
	draw_floor_and_ceiling(start_point, end_point, stripId);
	//printf("strpid = %f: start_point = %f: endpoint = %f\n", stripId, start_point, end_point);
	if (start_point < 0)
		start_point = 0;
	if (end_point > g_info.HIGHT)
		end_point = g_info.HIGHT;
	while (start_point < end_point)
	{
		mlx_put_pixel(g_info.image, stripId, start_point, ft_pixel(228, 147, 147, 255));
		start_point++;
	}
	draw_line_dda(g_info.minimap *  g_info.player.x, g_info.minimap * g_info.player.y, g_info.minimap * g_info.ray_x, g_info.minimap * g_info.ray_y);
}

void	draw_map(void* param)
{
	int		i;
	int 	j;

	i = 0;
	(void)param;
	draw_player();
	cast_all_ray();
	while (i < g_info.map_num_rows)
	{
		j = 0;
		while (j < g_info.map_num_colom)
		{
			if (g_info.map[i][j] == '1')
				squar_draw(g_info.minimap * (j * squire_size), g_info.minimap * (i * squire_size), g_info.minimap * squire_size,
					ft_pixel(255, 255, 255, 255), g_info.image);
			else if (g_info.map[i][j] == '0' || g_info.map[i][j] == 'N' || g_info.map[i][j] == 'S' || g_info.map[i][j] == 'W' || g_info.map[i][j] == 'E')
				squar_draw(g_info.minimap * (j * squire_size), g_info.minimap * (i * squire_size), g_info.minimap * squire_size,
					ft_pixel(0, 0, 0, 255), g_info.image);
			j++;
		}
		i++;
	}
}