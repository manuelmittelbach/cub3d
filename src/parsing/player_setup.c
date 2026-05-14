/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 11:40:00 by jnieders          #+#    #+#             */
/*   Updated: 2026/05/14 11:40:00 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir(t_data *d, double x, double y)
{
	d->dir_x = x;
	d->dir_y = y;
}

static void	set_plane(t_data *d, double x, double y)
{
	d->plane_x = x;
	d->plane_y = y;
}

static void	set_player_direction(t_data *d, char dir)
{
	if (dir == 'N')
	{
		set_dir(d, 0, -1);
		set_plane(d, 0.66, 0);
	}
	else if (dir == 'S')
	{
		set_dir(d, 0, 1);
		set_plane(d, -0.66, 0);
	}
	else if (dir == 'E')
	{
		set_dir(d, 1, 0);
		set_plane(d, 0, 0.66);
	}
	else if (dir == 'W')
	{
		set_dir(d, -1, 0);
		set_plane(d, 0, -0.66);
	}
}

void	set_player_data(t_data *d)
{
	int	i;
	int	j;

	i = -1;
	while (d->map.map_arr[++i])
	{
		j = -1;
		while (d->map.map_arr[i][++j])
		{
			if (!ft_strchr("NSEW", d->map.map_arr[i][j]))
				continue ;
			d->pos_x = j + 0.5;
			d->pos_y = i + 0.5;
			set_player_direction(d, d->map.map_arr[i][j]);
			return ;
		}
	}
}
