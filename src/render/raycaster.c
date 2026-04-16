/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15                                #+#    #+#             */
/*   Updated: 2026/04/15                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// header neu einfuegen spaeter!!! Ist verschoben!

// Hilfsfunktion: Konvertiert RGB-Werte aus dem Array in einen int-Farbcode
static int	get_rgb_color(int rgb[3])
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

// Malt die obere Haelfte des Bildschirms mit der Deckenfarbe (C)
// und die untere Haelfte mit der Bodenfarbe (F)
void	draw_floor_and_ceiling(t_data *d)
{
	int	x;
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = get_rgb_color(d->map.C);
	floor_color = get_rgb_color(d->map.F);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				ft_mlx_pixel_put(&d->screen, x, y, ceiling_color);
			else
				ft_mlx_pixel_put(&d->screen, x, y, floor_color);
			x++;
		}
		y++;
	}
}

// Berechnet alle Startwerte fuer einen einzelnen Strahl
static void	init_ray(t_data *d, t_ray *r, int x)
{
	double	camera_x;

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

// DDA-Loop: Springt von Gitterlinie zu Gitterlinie bis eine Wand getroffen wird
static void	run_dda(t_data *d, t_ray *r)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		// Welche naechste Gitterlinie ist naeher? X oder Y?
		if (r->side_dist_x < r->side_dist_y)
		{
			// X-Linie ist naeher: spring ein Kaestchen in X-Richtung
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			// Y-Linie ist naeher: spring ein Kaestchen in Y-Richtung
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		// Pruefe: Ist das aktuelle Kaestchen eine Wand?
		if (d->map.map_arr[r->map_y][r->map_x] == '1')
			hit = 1;
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
		
		// Schritt 1: Lotrechte Distanz zur Kameraebene berechnen (verhindert Fisheye-Effekt)
		// Wir nutzen die Tatsache, dass delta_dist genau ein Kästchen weit ist.
		// Da wir DDA gemacht haben, sind wir EIN delta_dist zu weit gegangen, also ziehen wir es wieder ab.
		double perp_wall_dist;
		if (r.side == 0)
			perp_wall_dist = (r.side_dist_x - r.delta_dist_x);
		else
			perp_wall_dist = (r.side_dist_y - r.delta_dist_y);

		// Verhindern einer Division durch null (falls dist 0 sein sollte, worauf wir theorethisch nie stoßen sollten bei einer validen Map)
		if (perp_wall_dist <= 0.000001)
			perp_wall_dist = 0.000001;

		// Schritt 2: Hoehe der Wand auf dem Bildschirm berechnen
		// Je weiter weg (groesseres perp_wall_dist), desto kleiner der line_height.
		int line_height;
		line_height = (int)(HEIGHT / perp_wall_dist);

		// Schritt 3: Start- und Endpunkt fuer den Pixelstrich auf dem Bildschirm berechnen
		// Die Wand soll genau in der Mitte der Y-Achse zentriert sein.
		int draw_start;
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0; // Nicht ueber den oberen Bildschirmrand hinaus malen

		int draw_end;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1; // Nicht ueber den unteren Bildschirmrand hinaus malen

		// Schritt 4: Helligkeit anpassen, um Ecken sichtbar zu machen
		int color;
		color = 0x00FF00; // Gruen fuer vertikale Waende (X-Achse, side == 0)
		if (r.side == 1)
			color = 0x008800; // Dunkelgruen fuer horizontale Waende (Y-Achse, side == 1)

		// Schritt 5: Den Streifen fuer diese spezifische x-Spalte von oben nach unten zeichnen
		int y = draw_start;
		while (y <= draw_end)
		{
			ft_mlx_pixel_put(&d->screen, x, y, color);
			y++;
		}

		x++;
	}
}

/*
// ======================== VISUALISIERUNG (AUSKOMMENTIERT) ========================

static void draw_test_line(t_data *d, int x0, int y0, int x1, int y1, int color)
{
	int dx; int sx;
	int dy; int sy;
	int err; int e2;
	int done;

	dx = abs(x1 - x0); sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0); sy = y0 < y1 ? 1 : -1;
	err = dx + dy; done = 0;
	while (!done)
	{
		if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT)
			ft_mlx_pixel_put(&d->screen, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			done = 1;
		else
		{
			e2 = 2 * err;
			if (e2 > dy) { err += dy; x0 += sx; }
			if (e2 < dx) { err += dx; y0 += sy; }
		}
	}
}

static void	draw_test_grid(t_data *d, int scale, int offset_x, int offset_y)
{
	int i; int j;
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			ft_mlx_pixel_put(&d->screen, i, j, 0x000000);
			j++;
		}
		i++;
	}
	i = offset_x;
	while (i > 0) i -= scale;
	while (i < WIDTH)
	{
		draw_test_line(d, i, 0, i, HEIGHT, 0x444444);
		i += scale;
	}
	j = offset_y;
	while (j > 0) j -= scale;
	while (j < HEIGHT)
	{
		draw_test_line(d, 0, j, WIDTH, j, 0x444444);
		j += scale;
	}
}

void	cast_rays_test(t_data *d)
{
	double	camera_x, ray_dir_x, ray_dir_y;
	int		map_x, map_y, step_x, step_y;
	double	delta_dist_x, delta_dist_y, side_dist_x, side_dist_y;
	int		scale = 120;
	int		px = WIDTH / 2;
	int		py = HEIGHT / 2;
	double math_pos_x = 0.5;
	double math_pos_y = 0.5;
	map_x = (int)math_pos_x;
	map_y = (int)math_pos_y;
	draw_test_grid(d, scale, px - (int)(math_pos_x * scale), py - (int)(math_pos_y * scale));
	draw_square(d, px - 4, py - 4, 9, 0x00FF00);
	draw_test_line(d, px, py, px + (d->dir_x * scale * 2), py + (d->dir_y * scale * 2), 0xFF0000);
	draw_test_line(d, px-1, py, px + (d->dir_x * scale * 2)-1, py + (d->dir_y * scale * 2), 0xFF0000);
	int plane_start_x = (px + (d->dir_x * scale * 2)) - (d->plane_x * scale * 2);
	int plane_start_y = (py + (d->dir_y * scale * 2)) - (d->plane_y * scale * 2);
	int plane_end_x = (px + (d->dir_x * scale * 2)) + (d->plane_x * scale * 2);
	int plane_end_y = (py + (d->dir_y * scale * 2)) + (d->plane_y * scale * 2);
	draw_test_line(d, plane_start_x, plane_start_y, plane_end_x, plane_end_y, 0x0000FF);
	draw_test_line(d, plane_start_x-1, plane_start_y, plane_end_x-1, plane_end_y, 0x0000FF);
	int x = 1000;
	camera_x = 2 * x / (double)WIDTH - 1;
	ray_dir_x = d->dir_x + d->plane_x * camera_x;
	ray_dir_y = d->dir_y + d->plane_y * camera_x;
	delta_dist_x = fabs(1.0 / ray_dir_x);
	delta_dist_y = fabs(1.0 / ray_dir_y);
	if (ray_dir_x < 0) { step_x = -1; side_dist_x = (math_pos_x - map_x) * delta_dist_x; }
	else { step_x = 1; side_dist_x = (map_x + 1.0 - math_pos_x) * delta_dist_x; }
	if (ray_dir_y < 0) { step_y = -1; side_dist_y = (math_pos_y - map_y) * delta_dist_y; }
	else { step_y = 1; side_dist_y = (map_y + 1.0 - math_pos_y) * delta_dist_y; }
	draw_test_line(d, px, py, px + (ray_dir_x * scale * 5), py + (ray_dir_y * scale * 5), 0xFFFFFF);
	int mark_x, mark_y;
	mark_x = px + (int)(ray_dir_x * side_dist_x * scale);
	mark_y = py + (int)(ray_dir_y * side_dist_x * scale);
	draw_square(d, mark_x - 5, mark_y - 5, 11, 0x00FFFF);
	mark_x = px + (int)(ray_dir_x * side_dist_y * scale);
	mark_y = py + (int)(ray_dir_y * side_dist_y * scale);
	draw_square(d, mark_x - 5, mark_y - 5, 11, 0xFF00FF);
	mark_x = px + (int)(ray_dir_x * (side_dist_x + delta_dist_x) * scale);
	mark_y = py + (int)(ray_dir_y * (side_dist_x + delta_dist_x) * scale);
	draw_square(d, mark_x - 5, mark_y - 5, 11, 0xFFA500);
	mark_x = px + (int)(ray_dir_x * (side_dist_y + delta_dist_y) * scale);
	mark_y = py + (int)(ray_dir_y * (side_dist_y + delta_dist_y) * scale);
	draw_square(d, mark_x - 5, mark_y - 5, 11, 0xFFFF00);
	(void)step_x; (void)step_y;
}
// ======================== VISUALISIERUNG ENDE ========================
*/
