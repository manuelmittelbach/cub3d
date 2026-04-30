/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:27:08 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/30 16:57:00 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

static void get_map_size(t_data *d, t_minimap *mm)
{
	while (d->map.map_arr[mm->map_height])
	{
		if ((int)ft_strlen(d->map.map_arr[mm->map_height]) > mm->map_width)
			mm->map_width = ft_strlen(d->map.map_arr[mm->map_height]);
		mm->map_height++;
	}
}

static int scale_rgb_color(int rgb[3], float factor)
{
	int	r;
	int	g;
	int	b;

	r = (int)(rgb[0] * factor);
	g = (int)(rgb[1] * factor);
	b = (int)(rgb[2] * factor);
	
	if (r > 255)
		r = 255;
	if (r < 0)
		r = 0;
	if (g > 255)
		g = 255;
	if (g < 0)
		g = 0;
	if (b > 255)
		b = 255;
	if (b < 0)
		b = 0;
	
	return (r << 16 | g << 8 | b);
}

void	init_minimap(t_data *d, t_minimap *mm)
{
	mm->d = d;
	mm->tile_size = WIDTH / 100;
	mm->map_width = 0;
	mm->map_height = 0;
	get_map_size(d, mm);
	mm->offset_x = (WIDTH * 0.03);
	mm->offset_y = (HEIGHT * 0.03);
	mm->color_wall = scale_rgb_color(d->map.F, 0.4);
	mm->color_floor = scale_rgb_color(d->map.F, 0.7);
	mm->color_player = scale_rgb_color(d->map.F, 2.0);
	mm->player_size = mm->tile_size / 3;
}
