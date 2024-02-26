/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_draw_sky.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:24:10 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/26 16:54:56 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"

void	rc_draw_sky(t_data *data)
{
	double	start;
	double	tex_len;
	
	tex_len = data->sky.width * (FOV_BASE / (M_PI * 2));
	printf("yaw:%f\n", data->player.euler_dir.y);
	start = (data->player.euler_dir.y * data->sky.width) / (M_PI * 2) - tex_len / 2;
	if (start < 0)
		start += data->sky.width;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->sky.img, -start, -WIN_HEIGHT / 2);
	// if (start + tex_len >= data->sky.width)
	// 	mlx_put_image_to_window(data->mlx, data->mlx_win, data->sky.img, data->sky.width - start, - WIN_HEIGHT / 2);
}