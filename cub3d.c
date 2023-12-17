/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:20:53 by asaber            #+#    #+#             */
/*   Updated: 2023/12/17 21:01:51 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_len_colom(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	get_maxlen(char **map)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

void	pre_init(int fd)
{
	g_info.buffer = malloc(BUFFER_SIZE);
	read(fd, g_info.buffer, BUFFER_SIZE);
	g_info.map = ft_split(g_info.buffer, '\n');
	g_info.map_num_colom = ft_strlen(g_info.map[4]);
	g_info.map_num_rows = map_len_colom(g_info.map);
	g_info.hight = g_info.map_num_rows * SQUIR_SIZE;
	g_info.wight = g_info.map_num_colom * SQUIR_SIZE;
	g_info.player.raduis = 3.0;
	g_info.player.walkdir = 0;
	g_info.player.turndir = 0;
	g_info.player.move_speed = 3.0;
	g_info.fov_angle = 60.0 * (M_PI / 180);
	g_info.player.turndir = 0;
	g_info.player.walkdir = 0;
	g_info.ray_x = 0;
	g_info.ray_y = 0;
	g_info.minimap = 0.2;
	find_player();
}

int	mlx_checks(mlx_t **mlx)
{
	*mlx = mlx_init(g_info.wight, g_info.hight, "cub3d", true);
	if (!*mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	g_info.image = mlx_new_image(*mlx, g_info.wight, g_info.hight);
	if (!g_info.image)
	{
		mlx_close_window(*mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(*mlx, g_info.image, 0, 0) == -1)
	{
		mlx_close_window(*mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	int		fd;
	mlx_t	*mlx;

	if (ac == 2)
	{
		fd = open(av[1], O_RDWR);
		pre_init(fd);
		if (mlx_checks(&mlx) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		mlx_loop_hook(mlx, draw_map, mlx);
		mlx_loop_hook(mlx, mlx_moves, mlx);
		mlx_loop(mlx);
		mlx_terminate(mlx);
	}
}
