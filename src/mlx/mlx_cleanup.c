/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:37:12 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/27 17:03:42 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->tex[i].img)
		{
			mlx_destroy_image(data->mlx, data->tex[i].img);
			data->tex[i].img = NULL;
		}
		i++;
	}
}

void	mlx_cleanup(t_data *data)
{
	cleanup_textures(data);
	if (data->screen.img)
	{
		mlx_destroy_image(data->mlx, data->screen.img);
		data->screen.img = NULL;
	}
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}
