/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:03:22 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/28 16:00:34 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define TILE_SIZE 24
#define OFFSET 40

static void	draw_square(t_data *d, int x, int y, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_mlx_pixel_put(&d->screen, x + j, y + i, color);
			j++;
		}
		i++;
	}
}
/*
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
*/



static void	get_map_size(t_data *d, int *w, int *h)
{
	*w = 0;
	*h = 0;
	while (d->map.map_arr[*h])
	{
		if ((int)ft_strlen(d->map.map_arr[*h]) > *w)
			*w = ft_strlen(d->map.map_arr[*h]);
		(*h)++;
	}
}

void	draw_minimap(t_data *d)
{
	int	y;
	int	x;
	int	color;
	int	off[2];
	int	map_size[2];

	get_map_size(d, &map_size[0], &map_size[1]);
	off[0] = WIDTH - map_size[0] * TILE_SIZE - OFFSET;
	off[1] = HEIGHT - map_size[1] * TILE_SIZE - OFFSET;
	y = -1;
	while (d->map.map_arr[++y])
	{
		x = -1;
		while (d->map.map_arr[y][++x])
		{
			if (d->map.map_arr[y][x] == '1')
				color = 0x222222;
			else if (d->map.map_arr[y][x] == '0' || ft_strchr("NSEW", d->map.map_arr[y][x]))
				color = 0x111111;
			else
				continue ;
			draw_square(d, off[0] + x * TILE_SIZE,
				off[1] + y * TILE_SIZE, TILE_SIZE, color);
		}
	}
	// hier brauchen wir eine bessere spieler zeichnung
	draw_square(d, off[0] + (int)(d->pos_x * TILE_SIZE) - 3, off[1] + (int)(d->pos_y * TILE_SIZE) - 3, 6, 0xFF0000);
}

