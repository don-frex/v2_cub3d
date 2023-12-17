/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 01:51:46 by asaber            #+#    #+#             */
/*   Updated: 2023/12/17 19:45:06 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	_x_y_to_check(int y, int x, char **map)
{
	unsigned int	tmpx;
	unsigned int	tmpy;

	if (x < 0 || y < 0 || x > (int) ft_strlen(map[y]) || y > (int) g_info.map_num_rows)
		return (0);
	tmpx = floor(x);
	tmpy = floor(y);
	if (map[tmpy][tmpx] != '1' && map[tmpy][tmpx] != 32 && map[tmpy][tmpx])
		return (1);
	return (0);
}