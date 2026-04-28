/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 12:08:06 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/28 14:30:15 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Mischt zwei Farben: t=0.0 ergibt c1, t=1.0 ergibt c2
static int blend_color(int c1, int c2, double t) {
  int r;
  int g;
  int b;

  r = (int)(((c1 >> 16) & 0xFF) * (1.0 - t) + ((c2 >> 16) & 0xFF) * t);
  g = (int)(((c1 >> 8) & 0xFF) * (1.0 - t) + ((c2 >> 8) & 0xFF) * t);
  b = (int)((c1 & 0xFF) * (1.0 - t) + (c2 & 0xFF) * t);
  return ((r << 16) | (g << 8) | b);
}

// Anti-Aliasing: Blendet die Rand-Pixel der Wand mit Decke/Boden
static void antialias_edges(t_data *d, int x, double exact_start, double exact_end)
{
  int wall_color;
  double frac;
  int y;

  // Oberkante: Pixel mit Deckenfarbe mischen
  y = (int)exact_start;
  if (exact_start > 0.0 && y >= 0 && y < HEIGHT)
  {
    frac = exact_start - floor(exact_start);
    wall_color = *(int *)(d->screen.addr + y * d->screen.line_length + x * (d->screen.bits_per_pixel / 8));
    ft_mlx_pixel_put(&d->screen, x, y, blend_color(get_rgb_color(d->map.C), wall_color, 1.0 - frac));
  }
 
  // Unterkante: Pixel mit Bodenfarbe mischen
  y = (int)exact_end;
  if (exact_end < (double)(HEIGHT - 1) && y >= 0 && y < HEIGHT)
  {
    frac = exact_end - floor(exact_end);
    wall_color = *(int *)(d->screen.addr + y * d->screen.line_length + x * (d->screen.bits_per_pixel / 8));
    ft_mlx_pixel_put(&d->screen, x, y, blend_color(wall_color, get_rgb_color(d->map.F), 1.0 - frac));
  }
}