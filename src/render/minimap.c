/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:01:15 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/13 17:15:48 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define TILE_SIZE 16

void	 draw_minimap(t_data *d)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (d->map.map_arr[y])
	{
		x = 0;
		while (d->map.map_arr[y][x])
		{
			if (d->map.map_arr[y][x] == '1')
				color = 0x808080;
			else if (d->map.map_arr[y][x] == '0' || ft_strchr("NSEW", d->map.map_arr[y][x]))
				color = 0xFFFFFF;
			else
				color = 0x000000;
			
			draw_square(d, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE - 1, color);
			x++;
		}
		y++;
	}

    
	// Zeichne den Spieler als kleinen roten Punkt
	draw_square(d, d->pos_x * TILE_SIZE - 2, d->pos_y * TILE_SIZE - 2, 4, 0xFF0000);
}
