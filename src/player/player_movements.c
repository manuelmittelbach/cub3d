/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:27:30 by jnieders          #+#    #+#             */
/*   Updated: 2026/05/12 14:32:12 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_wall(t_data *d, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	if (new_x < 0 || new_y < 0)
		return (true);
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (!d->map.map_arr[map_y])
		return (true);
	if (map_x >= (int)ft_strlen(d->map.map_arr[map_y]))
		return (true);
	if (d->map.map_arr[map_y][map_x] == '1')
		return (true);
	return (false);
}

void	move_player(t_data *d, double move_x, double move_y)
{
	double	target_x;
	double	target_y;

	target_x = d->pos_x + move_x;
	target_y = d->pos_y + move_y;

	if (is_wall(d, d->pos_x + move_x * 3, d->pos_y) == false)
		d->pos_x = target_x;
	if (is_wall(d, d->pos_x, d->pos_y + move_y * 3) == false)
		d->pos_y = target_y;
}

void	rotate_player(t_data *d, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = d->dir_x;
	d->dir_x = d->dir_x * cos(rot_speed) - d->dir_y * sin(rot_speed);
	d->dir_y = old_dir_x * sin(rot_speed) + d->dir_y * cos(rot_speed);
	old_plane_x = d->plane_x;
	d->plane_x = d->plane_x * cos(rot_speed) - d->plane_y * sin(rot_speed);
	d->plane_y = old_plane_x * sin(rot_speed) + d->plane_y * cos(rot_speed);
}
