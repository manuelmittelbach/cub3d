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

/*
int handle_keypress(int keycode, t_data *d)
{
	if (keycode == KEY_ESC)
		handle_close(d);
	if (keycode == KEY_W) 
		move_player(d, d->dir_x * MOVE_SPEED, d->dir_y * MOVE_SPEED);
	if (keycode == KEY_S)
		move_player(d, -d->dir_x * MOVE_SPEED, -d->dir_y * MOVE_SPEED);
	if (keycode == KEY_D)
		move_player(d, d->plane_x * MOVE_SPEED, d->plane_y * MOVE_SPEED);
	if (keycode == KEY_A)
		move_player(d, -d->plane_x * MOVE_SPEED, -d->plane_y * MOVE_SPEED);


	if (keycode == KEY_RIGHT)
	{
		double oldDirX = d->dir_x;
		d->dir_x = d->dir_x * cos(ROT_SPEED) - d->dir_y * sin(ROT_SPEED);
		d->dir_y = oldDirX * sin(ROT_SPEED) + d->dir_y * cos(ROT_SPEED);
		double oldPlaneX = d->plane_x;
		d->plane_x = d->plane_x * cos(ROT_SPEED) - d->plane_y * sin(ROT_SPEED);
		d->plane_y = oldPlaneX * sin(ROT_SPEED) + d->plane_y * cos(ROT_SPEED);
	}
	if (keycode == KEY_LEFT)
	{
		double oldDirX = d->dir_x;
		d->dir_x = d->dir_x * cos(-ROT_SPEED) - d->dir_y * sin(-ROT_SPEED);
		d->dir_y = oldDirX * sin(-ROT_SPEED) + d->dir_y * cos(-ROT_SPEED);
		double oldPlaneX = d->plane_x;
		d->plane_x = d->plane_x * cos(-ROT_SPEED) - d->plane_y * sin(-ROT_SPEED);
		d->plane_y = oldPlaneX * sin(-ROT_SPEED) + d->plane_y * cos(-ROT_SPEED);
	}
	return (0);
}
*/
