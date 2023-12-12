/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:32:38 by asaber            #+#    #+#             */
/*   Updated: 2023/12/11 23:16:41 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player(void)
{
	int	i;
	int	j;

	i = 0;
	while (g_info.map[i])
	{
		j = 0;
		while (g_info.map[i][j])
		{
			if (g_info.map[i][j] == 'N' || g_info.map[i][j] == 'S' || g_info.map[i][j] == 'W' || g_info.map[i][j] == 'E')
			{
				g_info.player.x = (squire_size * j) + (squire_size/2);
				g_info.player.y = (squire_size * i) + (squire_size/2);
				break ;
			}
			j++;
		}
		i++;
	}
}