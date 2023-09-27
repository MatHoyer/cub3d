/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:21:07 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/27 20:51:57 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	my_mlx_get_color(t_img_data img, int x, int y)
{
	char	*dst;

	dst = img.addr + (y * img.line_length + x * (img.bit_per_pixel
				/ 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_img_data *buffer, int x, int y, int color)
{
	char	*dst;

	dst = buffer->addr + (y * buffer->line_length + x * (buffer->bit_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}
