/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:36:03 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/13 17:24:26 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_close(t_data *data)
{
	cleanup(data);
	exit(0);
}


int handle_keypress(int keycode, t_data *d)
{
	if (keycode == KEY_ESC)
		handle_close(d);

	if (keycode == KEY_M)
    	d->show_minimap = !d->show_minimap;

	if (keycode == KEY_T)
		{
			d->mouse_active = !d->mouse_active;
			if (d->mouse_active == true)
			{
				mlx_mouse_hide(d->mlx, d->win);
				mlx_mouse_move(d->mlx, d->win, WIDTH / 2, HEIGHT / 2);
			}
			else
				mlx_mouse_show(d->mlx, d->win);

		}

	if (keycode >= 0 && keycode < 65536)
		d->keys[keycode] = true;
	return (0);
}

int	handle_keyrelease(int keycode, t_data *d)
{
	if (keycode >= 0 && keycode < 65536)
		d->keys[keycode] = false;
	return (0);
}


int handle_mouse_move(int x, int y, t_data *d)
{
	int movement_x;

	(void)y;
	if (d->mouse_active == false)
		return (0);

	// Schritt 3: Berechne den Unterschied zur Mitte
	movement_x = x - (WIDTH / 2);

	// Schritt 4 & 5: Wenn es eine Bewegung gab, drehe Spieler und setze Maus zurück
	if (movement_x != 0)
	{
		rotate_player(d, movement_x * MOUSE_SENS);
		mlx_mouse_move(d->mlx, d->win, WIDTH / 2, HEIGHT / 2); // Teleport in die Mitte!
	}
	return (0);
}


/*
int handle_mouse_move(int x, int y, t_data *d)
{
	static int prev_x = -1; // Speichert die X-Position aus dem letzten Frame
	int movement_x;

	(void)y;
	if (d->mouse_active == false)
	{
		prev_x = -1; // Reset, wenn die Maussteuerung aus ist
		return (0);
	}

	// Beim ersten Aufruf nach dem Einschalten haben wir noch keinen "alten" Wert
	if (prev_x == -1)
	{
		prev_x = x;
		return (0);
	}

	// Bewegung berechnen (Aktuelle Position - Letzte Position)
	movement_x = x - prev_x;

	// Spieler drehen
	if (movement_x != 0)
		rotate_player(d, movement_x * MOUSE_SENS);

	// Aktuelle Position für den nächsten Aufruf speichern
	prev_x = x;

	// --- DER WSL WORKAROUND ---
	// Wenn die Maus zu nah an den Rand kommt, setzen wir sie in die Mitte zurück.
	if (x < 100 || x > WIDTH - 100)
	{
		mlx_mouse_move(d->mlx, d->win, WIDTH / 2, HEIGHT / 2);
		prev_x = WIDTH / 2; // WICHTIG: prev_x auch in die Mitte setzen, sonst gibt es beim nächsten Frame eine wilde Drehung!
	}

	return (0);
}
*/
