/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:34:28 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/13 16:37:54 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture(t_data *data, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(data->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
		return (1);
	return (0);
}

int	load_textures(t_data *data, t_mapinfo *map)
{
	if (load_texture(data, &data->tex[0], map->NO))
		return (1);
	if (load_texture(data, &data->tex[1], map->SO))
		return (1);
	if (load_texture(data, &data->tex[2], map->WE))
		return (1);
	if (load_texture(data, &data->tex[3], map->EA))
		return (1);
	return (0);
}
