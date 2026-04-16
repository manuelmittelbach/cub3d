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

static bool	is_wall(t_data *d, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (d->map.map_arr[map_y][map_x] == '1')
		return (true);
		
	return (false);
}

int	handle_close(t_data *data)
{
	cleanup(data);
	exit(0);
}

static void	move_player(t_data *d, double move_x, double move_y)
{
	double	target_x;
	double	target_y;

	target_x = d->pos_x + move_x;
	target_y = d->pos_y + move_y;

	if (is_wall(d, target_x, d->pos_y) == false)
		d->pos_x = target_x;
		
	if (is_wall(d, d->pos_x, target_y) == false)
		d->pos_y = target_y;
}


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
