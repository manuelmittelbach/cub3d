/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:15:18 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/22 12:14:51 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// Malt die obere Haelfte des Bildschirms mit der Deckenfarbe (C)
// und die untere Haelfte mit der Bodenfarbe (F)
void draw_floor_and_ceiling(t_data *d) {
  int x;
  int y;
  int ceiling_color;
  int floor_color;

  ceiling_color = get_rgb_color(d->map.C);
  floor_color = get_rgb_color(d->map.F);
  y = 0;
  while (y < HEIGHT) {
    x = 0;
    while (x < WIDTH) {
      if (y < HEIGHT / 2)
        ft_mlx_pixel_put(&d->screen, x, y, ceiling_color);
      else
        ft_mlx_pixel_put(&d->screen, x, y, floor_color);
      x++;
    }
    y++;
  }
}

// Hauptfunktion: Schiesst 1280 Strahlen und zeichnet die Waende
void	cast_rays(t_data *d)
{
	int		x;
	t_ray	r;

	draw_floor_and_ceiling(d);
	x = 0;
	while (x < WIDTH)
	{
		init_ray(d, &r, x);
		run_dda(d, &r);
		render_wall_strip(d, &r, x);
		x++;
	}
}
