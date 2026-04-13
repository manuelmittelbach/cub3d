/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:47:28 by mmittelb          #+#    #+#             */
/*   Updated: 2026/04/13 14:17:08 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "check_input_file.h"

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->tex[i].img)
			mlx_destroy_image(data->mlx, data->tex[i].img);
		i++;
	}
	if (data->screen.img)
		mlx_destroy_image(data->mlx, data->screen.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int	handle_close(t_data *data)
{
	cleanup(data);
	exit(0);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		handle_close(data);
	return (0);
}

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

static int	load_textures(t_data *data, t_mapinfo *map)
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

static int	init_screen(t_data *data)
{
	data->screen.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->screen.img)
		return (1);
	data->screen.addr = mlx_get_data_addr(data->screen.img,
			&data->screen.bits_per_pixel,
			&data->screen.line_length,
			&data->screen.endian);
	if (!data->screen.addr)
		return (1);
	return (0);
}

static void	init_hooks(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win, 17, 0, handle_close, data);
}

int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	if (!data->win)
		return (mlx_destroy_display(data->mlx), free(data->mlx), 1);
	if (init_screen(data))
		return (cleanup(data), 1);
	if (load_textures(data, &data->map))
		return (cleanup(data), 1);
	init_hooks(data);
	return (0);
}
