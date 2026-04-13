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

	if (keycode == KEY_W) 
	{
		d->pos_x += d->dir_x * MOVE_SPEED;
		d->pos_y += d->dir_y * MOVE_SPEED;
	}
	if (keycode == KEY_S)
	{
		d->pos_x -= d->dir_x * MOVE_SPEED;
		d->pos_y -= d->dir_y * MOVE_SPEED;
	}
	if (keycode == KEY_D)
	{
		d->pos_x += d->plane_x * MOVE_SPEED;
		d->pos_y += d->plane_y * MOVE_SPEED;
	}
	if (keycode == KEY_A)
	{
		d->pos_x -= d->plane_x * MOVE_SPEED;
		d->pos_y -= d->plane_y * MOVE_SPEED;
	}
	return (0);
}
