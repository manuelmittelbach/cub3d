/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:04:23 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/13 17:05:56 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_frame(t_data *d)
{
	cast_rays(d);

	//draw_minimap(d);
	
	mlx_put_image_to_window(d->mlx, d->win, d->screen.img, 0, 0);
	return (0);
}
