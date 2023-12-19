/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:34:46 by asaber            #+#    #+#             */
/*   Updated: 2023/12/19 13:14:08 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_color(mlx_texture_t	*texture, int pix)
{
	uint32_t	color;
	uint8_t		red;
	uint8_t		green;
	uint8_t		blue;
	uint8_t		alpha;

	red = texture->pixels[pix++];
	green = texture->pixels[pix++];
	blue = texture->pixels[pix++];
	alpha = texture->pixels[pix];
	color = ft_pixel(red, green, blue, alpha);
	return (color);
}

void	squar_draw(float x, float y, int color, mlx_image_t *image, t_info *g_info)
{
	int	i;
	int	j;

	i = 0;
	while (i < SQUIR_SIZE * g_info->minimap)
	{
		j = 0;
		while (j < SQUIR_SIZE * g_info->minimap)
		{
			mlx_put_pixel(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_floor_and_ceiling(t_info *g_info, double s_p, double e_p, double stripId)
{
	while (s_p >= 0)
	{
		mlx_put_pixel(g_info->image, stripId, s_p, ft_pixel(197, 255, 248, 255));
		s_p--;
	}
	while (e_p <= g_info->hight)
	{
		mlx_put_pixel(g_info->image, stripId, e_p, ft_pixel(245, 232, 199, 255));
		e_p++;
	}
}

void	draw_by_diriction(t_info *g_info , double stripId, double start_point, double end_point)
{
	int	offsetx;
	int	offsety;
	int distancefromtop;

	if (g_info->hdist < g_info->vdist)
		offsetx = (int)g_info->ray_x % SQUIR_SIZE;
	else
		offsetx = (int)g_info->ray_y % SQUIR_SIZE;
	while (start_point < end_point)
	{
		distancefromtop = start_point + (g_info->wallstriphight / 2) - (g_info->hight / 2);
		offsety = distancefromtop * ((float)SQUIR_SIZE / g_info->wallstriphight);
		mlx_put_pixel(g_info->image, stripId, start_point, get_color(g_info->texture, ((g_info->texture->width * offsety) + offsetx) * 4));
		start_point++;
	}
}

void	draw_walls(double stripId, t_info *g_info)
{
	double	start_point;
	double	end_point;

	g_info->distprojectplane = (g_info->wight / 2) / tan(g_info->fov_angle / 2);
	g_info->f_dist = g_info->f_dist * 
		cos(g_info->ray_angle - g_info->player.rotation_angle);
	g_info->wallstriphight = 
		SQUIR_SIZE / g_info->f_dist * g_info->distprojectplane;
	start_point = (g_info->hight / 2) - (g_info->wallstriphight / 2);
	end_point = (g_info->hight / 2) + (g_info->wallstriphight / 2);
	g_info->start_point = (int)start_point;
	draw_floor_and_ceiling(g_info, start_point, end_point, stripId);
	if (start_point < 0)
		start_point = 0;
	if (end_point > g_info->hight)
		end_point = g_info->hight;
	draw_by_diriction(g_info, stripId, start_point, end_point);
}

void	draw_map(void *param)
{
	int	i;
	int	j;
	t_info *g_info;

	i = 0;
	g_info = (t_info *)param;
	draw_player(g_info);
	while (g_info->map[i])
	{
		j = 0;
		while (g_info->map[i][j])
		{
			if (g_info->map[i][j] == '1')
				squar_draw(g_info->minimap * (j * SQUIR_SIZE), g_info->minimap * 
					(i * SQUIR_SIZE), 
					ft_pixel(255, 255, 255, 255), g_info->image, g_info);
			else if (g_info->map[i][j] == '0' || g_info->map[i][j] == 'N' 
				|| g_info->map[i][j] == 'S' || g_info->map[i][j] == 'W' 
				|| g_info->map[i][j] == 'E')
				squar_draw(g_info->minimap * (j * SQUIR_SIZE), g_info->minimap * 
					(i * SQUIR_SIZE), ft_pixel(0, 0, 0, 255), g_info->image, g_info);
			j++;
		}
		i++;
	}
	draw_ray_angel(g_info);
}
