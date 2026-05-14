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
	mlx_cleanup(data);
	free_data(data);
	exit(0);
}

int	handle_keypress(int keycode, t_data *d)
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

int	handle_mouse_move(int x, int y, t_data *d)
{
	int	movement_x;

	(void)y;
	if (d->mouse_active == false)
		return (0);
	movement_x = x - (WIDTH / 2);
	if (movement_x != 0)
	{
		rotate_player(d, movement_x * MOUSE_SENS);
		mlx_mouse_move(d->mlx, d->win, WIDTH / 2, HEIGHT / 2);
	}
	return (0);
}
