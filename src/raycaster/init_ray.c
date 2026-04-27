/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:15:18 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/22 12:10:00 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Berechnet alle Startwerte fuer einen einzelnen Strahl
void	init_ray(t_data *d, t_ray *r, int x)
{
	double	camera_x;

	r->wall_dist = 0.0;
	// Pixelspalte x in den Bereich [-1, +1] umrechnen
	camera_x = 2 * x / (double)WIDTH - 1;

	// Endgueltige Flugrichtung dieses Strahls
	r->ray_dir_x = d->dir_x + d->plane_x * camera_x;
	r->ray_dir_y = d->dir_y + d->plane_y * camera_x;

	// In welchem Kaestchen steht der Spieler?
	r->map_x = (int)d->pos_x;
	r->map_y = (int)d->pos_y;

	// Konstante Schrittweite zwischen zwei Gitterlinien
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1.0 / r->ray_dir_x);

	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1.0 / r->ray_dir_y);

	// Schritt-Richtung und Startdistanz zur ersten Gitterlinie (X-Achse)
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (d->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - d->pos_x) * r->delta_dist_x;
	}

	// Schritt-Richtung und Startdistanz zur ersten Gitterlinie (Y-Achse)
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (d->pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - d->pos_y) * r->delta_dist_y;
	}
}
