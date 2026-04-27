/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:15:18 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/22 12:03:00 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// DDA-Loop: Springt von Gitterlinie zu Gitterlinie bis eine Wand getroffen wird
void	run_dda(t_data *d, t_ray *r)
{
	int	hit_flag;

	hit_flag = 0;
	while (hit_flag == 0)
	{
		// Welche naechste Gitterlinie ist naeher? X oder Y?
		if (r->side_dist_x < r->side_dist_y)
		{
			// X-Linie ist naeher: spring ein Kaestchen in X-Richtung
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->hit = HIT_VERTICAL;
		}
		else
		{
			// Y-Linie ist naeher: spring ein Kaestchen in Y-Richtung
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->hit = HIT_HORIZONTAL;
		}

		// Pruefe: Ist das aktuelle Kaestchen eine Wand?
		if (d->map.map_arr[r->map_y][r->map_x] == '1')
		{
			hit_flag = 1;
			// Bereinigung des DDA-Overshoots:
			// Da wir in der Schleife ein Feld zu weit (in die Wand hinein)
			// gesprungen sind, ziehen wir das letzte delta_dist wieder ab.
			if (r->hit == HIT_VERTICAL)
				r->wall_dist = r->side_dist_x - r->delta_dist_x;
			else
				r->wall_dist = r->side_dist_y - r->delta_dist_y;

			// Schutzklausel: Verhindert Division durch Null beim spaeteren
			// Render-Vorgang.
			if (r->wall_dist <= 0.000001)
				r->wall_dist = 0.000001;
		}
	}
}
