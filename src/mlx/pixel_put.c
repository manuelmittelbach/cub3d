/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:37:12 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/22 11:55:00 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));

	*(unsigned int *)dst = color;
}

void	draw_square(t_data *d, int x, int y, int size, int color)
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
