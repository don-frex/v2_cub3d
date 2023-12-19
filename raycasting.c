/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:05:51 by asaber            #+#    #+#             */
/*   Updated: 2023/12/19 16:10:19 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//!! yassir's function is changed
void	get_texture(t_info *g_info)
{
	if (g_info->vdist == g_info->f_dist)
	{
		if (g_info->left == 1)
			g_info->texture = g_info->W;
		else if (g_info->right == 1)
			g_info->texture = g_info->E;
	}
	else
	{
		if (g_info->up == 1)
			g_info->texture = g_info->N;
		else if (g_info->down == 1)
			g_info->texture = g_info->S;
	}
}

void	updateraydirection(t_info *g_info)
{
	if (g_info->ray_angle > 0 && g_info->ray_angle < M_PI)
		g_info->israyfacingdown = 1;
	else
		g_info->israyfacingdown = 0;
	g_info->israyfacingup = !g_info->israyfacingdown;
	if (g_info->ray_angle < 0.5 * M_PI || g_info->ray_angle > 1.5 * M_PI)
		g_info->israyfacingright = 1;
	else
		g_info->israyfacingright = 0;
	g_info->israyfacingleft = !g_info->israyfacingright;
}

int	check_wall(char **map, int square_size, double x, double y, t_info *g_info)
{
	int	x_map;
	int	y_map;

	if (x < 0 || y < 0 || x / SQUIR_SIZE > ft_strlen(map[(int)y / 
				SQUIR_SIZE]) || y / SQUIR_SIZE > g_info->map_num_rows)
		return (1);
	x_map = floor(x / square_size);
	y_map = floor(y / square_size);
	if (map[y_map][x_map] == '1' || map[y_map][x_map] == 32)
		return (1);
	return (0);
}

int	has_wall_at(double player_x, double player_y, t_info *g_info)
{
	double	x;
	double	y;

	x = player_x / SQUIR_SIZE; 
	y = player_y / SQUIR_SIZE;
	if (y < 0 || y >= g_info->map_num_rows)
		return (1);
	if (x < 0 || x > g_info->map_num_colom)
		return (1);
	if (g_info->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}
void	cast_horizontal(t_raycasting *raycast, t_info *g_info)
{
	g_info->hfoundwall = false;
	raycast->yinterseption = floor(g_info->player.y / SQUIR_SIZE) * SQUIR_SIZE;
	raycast->yinterseption += g_info->israyfacingdown ? SQUIR_SIZE : 0;
	raycast->xinterseption = g_info->player.x + (raycast->yinterseption - g_info->player.y) / 
		tan(g_info->ray_angle);
	g_info->ystep = SQUIR_SIZE;
	g_info->ystep *= g_info->israyfacingup ? -1 : 1;
	g_info->xstep = SQUIR_SIZE / tan(g_info->ray_angle);
	g_info->xstep *= (g_info->israyfacingleft && g_info->xstep > 0) ? -1 : 1;
	g_info->xstep *= (g_info->israyfacingright && g_info->xstep < 0) ? -1 : 1;
	raycast->nexth_x = raycast->xinterseption;
	raycast->nexth_y = raycast->yinterseption;
	if (g_info->israyfacingup)
		raycast->nexth_y--;
	while (raycast->nexth_x >= 0 && raycast->nexth_x <= g_info->wight && 
		raycast->nexth_y >= 0 && raycast->nexth_y <= g_info->hight)
	{
		if (check_wall(g_info->map, SQUIR_SIZE, raycast->nexth_x, raycast->nexth_y, g_info))
		{
			g_info->hray_x = raycast->nexth_x;
			g_info->hray_y = raycast->nexth_y;
			g_info->hfoundwall = true;
			break ;
		}
		else
		{
			raycast->nexth_x += g_info->xstep;
			raycast->nexth_y += g_info->ystep;
		}
	}
}

void	cast_vertical(t_raycasting *raycast, t_info *g_info)
{
	g_info->vfoundwall = false;
	raycast->xinterseption_v = floor(g_info->player.x / SQUIR_SIZE) * SQUIR_SIZE;
	raycast->xinterseption_v += g_info->israyfacingright ? + SQUIR_SIZE : 0;
	raycast->yinterseption_v = g_info->player.y + 
		(raycast->xinterseption_v - g_info->player.x) * tan(g_info->ray_angle);
	g_info->xstep = SQUIR_SIZE;
	g_info->xstep *= g_info->israyfacingleft ? -1 : 1;
	g_info->ystep = SQUIR_SIZE * tan(g_info->ray_angle);
	g_info->ystep *= (g_info->israyfacingup && g_info->ystep > 0) ? -1 : 1;
	g_info->ystep *= (g_info->israyfacingdown && g_info->ystep < 0) ? -1 : 1;
	raycast->nextv_y = raycast->yinterseption_v;
	raycast->nextv_x = raycast->xinterseption_v;
	if (g_info->israyfacingleft)
		raycast->nextv_x--;
	while (raycast->nextv_x >= 0 && raycast->nextv_x <= g_info->wight && 
		raycast->nextv_y >= 0 && raycast->nextv_y <= g_info->hight)
	{
		if (check_wall(g_info->map, SQUIR_SIZE, raycast->nextv_x, raycast->nextv_y, g_info))
		//if (_x_y_to_check(raycast->nextv_y / SQUIR_SIZE, raycast->nextv_x, g_info->map))
		{
			g_info->vray_x = raycast->nextv_x;
			g_info->vray_y = raycast->nextv_y;
			g_info->vfoundwall = true;
			break ;
		}
		else
		{
			raycast->nextv_x += g_info->xstep;
			raycast->nextv_y += g_info->ystep;
		}
	}
}

void	check_distence(t_raycasting *raycast, t_info *g_info)
{
	if (g_info->hfoundwall)
		g_info->hdist = sqrt((raycast->nexth_x - g_info->player.x) * 
				(raycast->nexth_x - g_info->player.x) + (raycast->nexth_y - 
					g_info->player.y) * (raycast->nexth_y - g_info->player.y));
	else
		g_info->hdist = MAXFLOAT;
	if (g_info->vfoundwall)
		g_info->vdist = sqrt((raycast->nextv_x - g_info->player.x) * 
				(raycast->nextv_x - g_info->player.x) + (raycast->nextv_y - 
					g_info->player.y) * (raycast->nextv_y - g_info->player.y));
	else
		g_info->vdist = MAXFLOAT;
	if (g_info->vdist < g_info->hdist)
	{
		g_info->f_dist = g_info->vdist;
		g_info->ray_x = g_info->vray_x;
		g_info->ray_y = g_info->vray_y;
	}
	else
	{
		g_info->f_dist = g_info->hdist;
		g_info->ray_x = g_info->hray_x;
		g_info->ray_y = g_info->hray_y;
	}
}

void	main_cast(t_info *g_info)
{
	t_raycasting	*raycast;

	raycast = malloc(sizeof(t_raycasting));
	updateraydirection(g_info);
	cast_horizontal(raycast, g_info);
	cast_vertical(raycast, g_info);
	check_distence(raycast, g_info);
}

void	draw_line_dda(int x1, int y1, int x2, int y2, mlx_image_t *image)
{
	int		i;
	int		dx;
	int		dy;
	int		steps;
	double	xincrement;
	double	yincrement;
	double	x;
	double	y;

	x = x1;
	y = y1;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	xincrement = (double)dx / (double)steps;
	yincrement = (double)dy / (double)steps;
	i = 0;
	while (i < steps)
	{
		mlx_put_pixel(image, round(x), round(y), 0xFFFFFF);
		x += xincrement;
		y += yincrement;
		i++;
	}
}

double normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	return (fmod(angle, 2 * M_PI));
}
//!! yassir's function is changed
void	ray_view(double angle, t_info *g_info)
{
	g_info->up = 0;
	g_info->down = 0;
	g_info->left = 0;
	g_info->right = 0;
	if (angle > 0 && angle < M_PI)
		g_info->down = 1;
	else
		g_info->up = 1;
	if (angle < M_PI * 0.5 || angle > 1.5 * M_PI)
		g_info->right = 1;
	else
		g_info->left = 1;
	get_texture(g_info);
}

void	cast_all_ray(t_info *g_info)
{
	unsigned int	i;

	g_info->ray_angle = g_info->player.rotation_angle - (g_info->fov_angle / 2);
	i = 0;
	while (i < g_info->wight)
	{
		main_cast(g_info);
		g_info->ray_angle += g_info->fov_angle / g_info->wight;
		g_info->player.rotation_angle = 
			normalize_angle(g_info->player.rotation_angle);
		g_info->ray_angle = normalize_angle(g_info->ray_angle);
		ray_view(g_info->ray_angle, g_info);
		draw_walls(i++, g_info);
	}
}
