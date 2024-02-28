/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:58:46 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/26 19:00:36 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"
#include "../libft_s/libft_s.h"

void	rc_get_tex_x(t_data *data, t_rc_data *rc_data, t_draw_data *d_data, t_vec2 ray)
{
	if (rc_data->side && ray.x > 0)
		d_data->type = TC_EA;
	else if (rc_data->side && ray.x < 0)
		d_data->type = TC_WE;
	else if (ray.y > 0)
		d_data->type = TC_SO;
	else
		d_data->type = TC_NO;
	if (rc_data->side)
		d_data->wall_x = data->player.pos.y + d_data->dist * ray.y;
	else
		d_data->wall_x = data->player.pos.x + d_data->dist * ray.x;
	if (d_data->type == TC_NO || d_data->type == TC_EA)
		d_data->wall_x = d_data->wall_x - floor(d_data->wall_x);
	else
		d_data->wall_x = ceil(d_data->wall_x) - d_data->wall_x;
	d_data->tex_x =	d_data->wall_x * (double)data->tex[d_data->type].width;
}

void	rc_draw_col(t_data *data, t_vec2 ray, int x)
{
	int			i;
	t_draw_data	d_data;
	t_rc_data	rc_data;

	rc_get_distance(data, &rc_data, &d_data, ray);
	rc_get_tex_x(data, &rc_data, &d_data, ray);
	d_data.tex_h = (int)(WIN_HEIGHT / d_data.dist) * FOV_BASE / data->player.fov;
	d_data.start = -d_data.tex_h / 2 + WIN_HEIGHT / 2 \
		+ data->player.pos.z / d_data.dist + data->player.euler_dir.x;
	d_data.end = d_data.tex_h / 2 + WIN_HEIGHT / 2 \
		+ data->player.pos.z / d_data.dist + data->player.euler_dir.x;
	d_data.offset = d_data.start;
	if (d_data.start < 0)
		d_data.start = 0;
	if (d_data.end >= WIN_HEIGHT)
		d_data.end = WIN_HEIGHT - 1;
	i = 0;
	while (i < d_data.start)
		utils_draw_point(data, x, i++, 0XFF000000);
	while (i < d_data.end)
	{
		d_data.color = data->tex[d_data.type].data[((i - d_data.offset) * data->tex[d_data.type].height) / d_data.tex_h][d_data.tex_x];
		utils_draw_point(data, x, i++, d_data.color);
	}
	// while (i < WIN_HEIGHT)
	// 	utils_draw_point(data, x, i++, data->f_color);
}

void	rc_raycast(t_data *data)
{
	int	i;

	pthread_create(&(data->t_id[0]), NULL, (void *)rc_thread0, (void *)data);
	pthread_create(&(data->t_id[1]), NULL, (void *)rc_thread1, (void *)data);
	pthread_create(&(data->t_id[2]), NULL, (void *)rc_thread2, (void *)data);
	i = 0;
	while (i < 3)
		pthread_join(data->t_id[i++], NULL);
}
