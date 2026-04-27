/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:17:00 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/27 19:09:55 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Bestimmt die Textur-Nummer anhand der Himmelsrichtung
static int get_tex_num(t_ray *r) {
	if (r->hit == HIT_VERTICAL) {
		if (r->ray_dir_x > 0)
			return (3);
		return (2);
	}
	if (r->ray_dir_y > 0)
		return (1);
	return (0);
}

// Berechnet wo genau am Kaestchen der Strahl getroffen hat (0.0 bis 1.0)
static void	get_tex_column(t_data *d, t_ray *r, t_wall *w, int tex_width)
{
	double	hit_pos;

	if (r->hit == HIT_VERTICAL)
		hit_pos = d->pos_y + r->wall_dist * r->ray_dir_y;
	else
		hit_pos = d->pos_x + r->wall_dist * r->ray_dir_x;
	hit_pos = hit_pos - floor(hit_pos);


	w->tex_col = (int)(hit_pos * (double)tex_width);

	// Textur spiegeln, damit sie an den richtigen Seiten korrekt anliegt
	if ((r->hit == HIT_VERTICAL && r->ray_dir_x < 0) ||
			(r->hit == HIT_HORIZONTAL && r->ray_dir_y > 0))
		w->tex_col = tex_width - w->tex_col - 1;
}

static void	draw_strip(t_data *d, t_img *tex, t_wall *w, int x)
{
	int	tex_row;
	int	color;

	while (w->start <= w->end)
	{
		// Aktuelle Y-Koordinate in der Textur bestimmen
		tex_row = (int)w->tex_pos;
		if (tex_row >= tex->height)
			tex_row = tex->height - 1;
		w->tex_pos += w->step;
		
		// Farbe direkt aus dem Speicher der Textur auslesen
		color = *(int *)(tex->addr + (tex_row * tex->line_length) + \
				(w->tex_col * (tex->bits_per_pixel / 8)));
		
		// Pixel in den Screen-Buffer setzen
		ft_mlx_pixel_put(&d->screen, x, w->start, color);
		w->start++;
	}
}



// Zeichnet einen vertikalen Wandstreifen mit Textur
void	render_wall_strip(t_data *d, t_ray *r, int x)
{
	t_img	*tex;
	t_wall	w;

	// 1. Die richtige Textur anhand der Himmelsrichtung waehlen
	tex = &d->tex[get_tex_num(r)];

	// 2. Hoehe der Wand auf dem Bildschirm berechnen
	w.height = (int)(HEIGHT / r->wall_dist);

	// 3. Start- und Endpunkt berechnen (zentriert auf der Y-Achse)
	w.start = (HEIGHT / 2) - (w.height / 2);
	if (w.start < 0)
		w.start = 0;
	w.end = (w.height / 2) + (HEIGHT / 2);
	if (w.end >= HEIGHT)
		w.end = HEIGHT - 1;

	// 4. Berechnen, welche Spalte (w->tex_col) der Textur wir zeichnen muessen
	get_tex_column(d, r, &w, tex->width);


	// 5. Schrittweite (wie viele Texturpixel pro Screenpixel) festlegen
	w.step = 1.0 * tex->height / w.height;
	// Startposition in der Textur berechnen
	w.tex_pos = (w.start - (HEIGHT / 2 - w.height / 2)) * w.step;
	
	// 6. Den vertikalen Streifen von oben nach unten zeichnen
	draw_strip(d, tex, &w, x);
}















// DIESE FUNKTION FUNKTIONIERT, ALSO KEIN WOBBELN, ABER SEG FAULT

/*
void	render_wall_strip(t_data *d, t_ray *r, int x)
{
	t_img	*tex;
	t_wall	w;
	double	exact_height; // Wir nutzen double für die Präzision

	tex = &d->tex[get_tex_num(r)];

	// 1. Höhe als double berechnen, nicht sofort casten
	exact_height = (double)HEIGHT / r->wall_dist;
	w.height = (int)exact_height;

	// 2. Start- und Endpunkt präziser berechnen
	// Wir ziehen die halbe exakte Höhe von der Mitte ab
	w.start = (int)((double)HEIGHT / 2.0 - exact_height / 2.0);
	w.end = (int)((double)HEIGHT / 2.0 + exact_height / 2.0);

	// 3. Clipping (wie gehabt, aber w.end muss exklusiver sein)
	if (w.start < 0) w.start = 0;
	if (w.end >= HEIGHT) w.end = HEIGHT - 1;

	// 4. Textur-Berechnung
	get_tex_column(d, r, &w, tex->width);
	w.step = (double)tex->height / exact_height;
	
	// Startposition in der Textur basierend auf dem (evtl. geklippten) w.start
	// Wir berechnen, wie weit w.start von der theoretisch perfekten Mitte weg ist
	w.tex_pos = (w.start - ((double)HEIGHT / 2.0 - exact_height / 2.0)) * w.step;
	
	draw_strip(d, tex, &w, x);
}
*/
















// DIESE FUNKTION FUNKTIONIERT, ALSO KEIN WOBBELN, BISHER KEIN SEG FAULT
// --> muss noch mehr getestet werden

/*
static void	draw_strip(t_data *d, t_img *tex, t_wall *w, int x)
{
	int	tex_row;
	int	color;

	while (w->start <= w->end)
	{
		tex_row = (int)w->tex_pos;
		
		// SCHUTZ: Darf nicht negativ sein
		if (tex_row < 0)
			tex_row = 0;
		// SCHUTZ: Darf nicht größer als die Texturhöhe sein
		if (tex_row >= tex->height)
			tex_row = tex->height - 1;
			
		w->tex_pos += w->step;
		
		// SCHUTZ: Auch die Spalte (tex_col) muss validiert werden
		if (w->tex_col < 0)
			w->tex_col = 0;
		if (w->tex_col >= tex->width)
			w->tex_col = tex->width - 1;

		// Jetzt ist der Speicherzugriff sicher
		color = *(int *)(tex->addr + (tex_row * tex->line_length) + \
				(w->tex_col * (tex->bits_per_pixel / 8)));
		
		ft_mlx_pixel_put(&d->screen, x, w->start, color);
		w->start++;
	}
}

void	render_wall_strip(t_data *d, t_ray *r, int x)
{
	t_img	*tex;
	t_wall	w;
	double	exact_height;

	tex = &d->tex[get_tex_num(r)];
	exact_height = (double)HEIGHT / r->wall_dist;
	w.height = (int)exact_height;

	// Start und Ende berechnen
	w.start = (int)((double)HEIGHT / 2.0 - exact_height / 2.0);
	w.end = (int)((double)HEIGHT / 2.0 + exact_height / 2.0);

	// Clipping für den Bildschirm
	if (w.start < 0) w.start = 0;
	if (w.end >= HEIGHT) w.end = HEIGHT - 1;

	// Textur-Spalte berechnen
	get_tex_column(d, r, &w, tex->width);

	// Schrittweite basierend auf der EXAKTEN Höhe
	w.step = (double)tex->height / exact_height;
	
	// Startposition in der Textur (sehr wichtig für korrekte Rundung)
	w.tex_pos = (w.start - ((double)HEIGHT / 2.0 - exact_height / 2.0)) * w.step;
	
	draw_strip(d, tex, &w, x);
}
*/