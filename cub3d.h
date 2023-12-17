/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:20:02 by asaber            #+#    #+#             */
/*   Updated: 2023/12/17 19:29:00 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "/Users/asaber/MLX42/include/MLX42/MLX42.h"

# define SQUIR_SIZE 32
# define BUFFER_SIZE 500000

typedef struct playerinfo
{
	double	x;
	double	y;
	double	raduis;
	int		turndir;
	int		walkdir;
	double	rotation_angle;
	double	move_speed;
	double	rotation_speed;
}	t_player;

typedef struct raycasting
{
	double	yinterseption;
	double	xinterseption;
	double	xinterseption_v;
	double	yinterseption_v;
	double	nexth_x;
	double	nexth_y;
	double	nextv_x;
	double	nextv_y;
}	t_raycasting;

typedef struct gameinfo
{
	mlx_image_t		*image;
	char			*buffer;
	char			**map;
	int				map_num_rows;
	int				map_num_colom;
	unsigned int	hight;
	unsigned int	wight;
	double			fov_angle;
	double			ray_angle;
	bool			israyfacingdown;
	bool			israyfacingup;
	bool			israyfacingright;
	bool			israyfacingleft;
	double			xintercept;
	double			yintercept;
	double			hdist;
	double			vdist;
	double			f_dist;
	double			xstep;
	double			ystep;
	double			ray_x;
	double			ray_y;
	double			hray_x;
	double			hray_y;
	double			vray_x;
	double			vray_y;
	double			distprojectplane;
	double			wallstriphight;
	double			minimap;
	bool			hfoundwall;
	bool			vfoundwall;
	t_player		player;

}	t_info;

t_info	g_info;

char	**ft_split(char const *s, char c);
int		ft_strlen(char *str);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	draw_map(void *param);
void	mlx_moves(void *param);
void	move_player(void);
void	find_player(void);
int		_x_y_to_check(int y, int x, char **map);
void	draw_line_dda(int x1, int y1, int x2, int y2);
void	cast_all_ray(void);
void	draw_walls(double stripId);
void	draw_player(void);
void	draw_ray_angel(void);

#endif