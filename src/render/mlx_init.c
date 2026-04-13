/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:47:28 by mmittelb          #+#    #+#             */
/*   Updated: 2026/04/13 17:04:06 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "check_input_file.h"

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

	mlx_loop_hook(data->mlx, render_frame, data);
	
	return (0);
}
