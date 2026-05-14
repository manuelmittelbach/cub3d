/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 12:21:54 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/30 12:21:54 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

static void	draw_mm(t_minimap *mm, int x, int y, int color)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	i = 0;
	start_x = mm->offset_x + x * mm->tile_size;
	start_y = mm->offset_y + y * mm->tile_size;
	while (i < mm->tile_size)
	{
		j = 0;
		while (j < mm->tile_size)
		{
			ft_mlx_pixel_put(&mm->d->screen, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_view_direction(t_minimap *mm, int player_x, int player_y)
{
	int	center_x;
	int	center_y;
	int	i;
	int	dot_x;
	int	dot_y;

	center_x = player_x + (mm->player_size / 2);
	center_y = player_y + (mm->player_size / 2);
	i = 1;
	while (i <= 3)
	{
		dot_x = center_x + (int)(mm->d->dir_x * i * mm->tile_size / 6);
		dot_y = center_y + (int)(mm->d->dir_y * i * mm->tile_size / 6);
		ft_mlx_pixel_put(&mm->d->screen, dot_x, dot_y, mm->color_player);
		ft_mlx_pixel_put(&mm->d->screen, dot_x + 1, dot_y, mm->color_player);
		ft_mlx_pixel_put(&mm->d->screen, dot_x, dot_y + 1, mm->color_player);
		ft_mlx_pixel_put(&mm->d->screen, dot_x + 1, dot_y + 1,
			mm->color_player);
		i++;
	}
}

static void	draw_player(t_minimap *mm, int c)
{
	int	i;
	int	j;
	int	player_x;
	int	player_y;

	i = 0;
	player_x = mm->offset_x + (int)(mm->d->pos_x * mm->tile_size)
		- (mm->player_size / 2);
	player_y = mm->offset_y + (int)(mm->d->pos_y * mm->tile_size)
		- (mm->player_size / 2);
	while (i < mm->player_size)
	{
		j = 0;
		while (j < mm->player_size)
		{
			ft_mlx_pixel_put(&mm->d->screen, player_x + j, player_y + i, c);
			j++;
		}
		i++;
	}
	draw_view_direction(mm, player_x, player_y);
}

void	draw_minimap(t_data *d)
{
	t_minimap	mm;
	int			y;
	int			x;
	char		**map;

	init_minimap(d, &mm);
	map = d->map.map_arr;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_mm(&mm, x, y, mm.color_wall);
			else if (map[y][x] == '0' || ft_strchr("NSEW", map[y][x]))
				draw_mm(&mm, x, y, mm.color_floor);
			x++;
		}
		y++;
	}
	draw_player(&mm, mm.color_player);
}
