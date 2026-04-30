/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:05:15 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/28 14:36:47 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

int	render_frame(t_data *d)
{
	if (d->keys[KEY_W] == true)
		move_player(d, d->dir_x * MOVE_SPEED, d->dir_y * MOVE_SPEED);
	if (d->keys[KEY_S] == true)
		move_player(d, -d->dir_x * MOVE_SPEED, -d->dir_y * MOVE_SPEED);
	if (d->keys[KEY_A] == true)
		move_player(d, -d->plane_x * MOVE_SPEED, -d->plane_y * MOVE_SPEED);
	if (d->keys[KEY_D] == true)
		move_player(d, d->plane_x * MOVE_SPEED, d->plane_y * MOVE_SPEED);
	if (d->keys[KEY_LEFT] == true)
		rotate_player(d, -ROT_SPEED);
	if (d->keys[KEY_RIGHT] == true)
		rotate_player(d, ROT_SPEED);

	
	cast_rays(d);
	draw_minimap(d);
	mlx_put_image_to_window(d->mlx, d->win, d->screen.img, 0, 0);
	return (0);
}
