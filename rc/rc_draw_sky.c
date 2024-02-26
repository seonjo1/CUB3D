/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_draw_sky.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:24:10 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/26 20:00:04 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"

void	rc_draw_sky(t_data *data)
{
	double	yaw;
	double	mod;
	double	start;
	double	tex_len;
	
	yaw = data->player.euler_dir.y;
	if (yaw < 0)
	{
		mod = fmod(yaw, 6.28);
		yaw = 6.28 + mod;
	}
	else if (yaw >= 6.28)
		yaw = fmod(yaw, 6.28);
	// printf("yaw : %f\n", yaw);
	tex_len = data->sky.width * (FOV_BASE / (M_PI * 2));
	start = (yaw * data->sky.width) / (M_PI * 2) - tex_len / 2;
	if (start < 0)
		start += data->sky.width;
	// printf("start : %f sky_width : %d\n", start, data->sky.width);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->sky.img, -start, -WIN_HEIGHT / 2);
	if (data->sky.width - start < WIN_WIDTH)
	{
		// printf("sky_width - start : %f\n", data->sky.width - start);
		// printf("sky_width - start : %d\n",(int) (data->sky.width - start));
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->sky.img, (int)(data->sky.width - start), - WIN_HEIGHT / 2);
	}
}