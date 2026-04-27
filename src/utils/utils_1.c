/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:01:47 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/01 18:02:15 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	if (!str_arr)
		return ;
	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
	return ;
}

int	get_rgb_color(int rgb[3])
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
