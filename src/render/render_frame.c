/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:04:23 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/13 17:05:56 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_frame(t_data *d)
{
	// 1. Hintergrund schwarz machen (Bildschirm löschen)
	// (Optional: Später zeichnen wir hier Himmel und Boden)
	
	// 2. Map und Spieler zeichnen
	draw_minimap(d);
	
	// 3. Das fertige Bild ins Fenster pushen
	mlx_put_image_to_window(d->mlx, d->win, d->screen.img, 0, 0);
	return (0);
}
