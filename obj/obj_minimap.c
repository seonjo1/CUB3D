/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:43:44 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/19 14:13:46 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include "../libft_s/libft_s.h"

void	obj_draw_aim(t_data *data)
{
	t_intvec2	aim;
	int			i;
	const int	aim_size = 20;

	aim.x = (WIN_WIDTH >> 1) - aim_size;
	aim.y = (WIN_HEIGHT >> 1);
	i = -1;
	while (++i < (aim_size << 1))
		utils_draw_point(data, aim.x + i, aim.y, 0xFF00FF);
	aim.x = (WIN_WIDTH >> 1);
	aim.y = (WIN_HEIGHT >> 1) - aim_size;
	i = -1;
	while (++i < (aim_size << 1))
		utils_draw_point(data, aim.x, aim.y + i, 0xFF00FF);
}

void	obj_mini_init(t_data *data)
{
	if (WIN_WIDTH > WIN_HEIGHT)
		data->mini.size = WIN_HEIGHT / 5;
	else
		data->mini.size = WIN_WIDTH / 5;
	if (!(data->mini.size % 2))
		data->mini.size += 1;
	data->mini.ratio = 10;
}

void	obj_draw_mini_player(t_data *data, int center, int h)
{
	static int sign[2] = {-1, 1};
	int	level;
	int	x;
	int	i;

	level = 0;
	while (level < 2)
	{
		x = h * sign[level];
		while (x != -sign[level])
		{
			i = x * sign[level];
			while (i >= -h + 2 * x * sign[level])
				utils_draw_point(data, x + center, i-- + center, 0xffffff);
			x -= sign[level];
		}
		level++;
	}
}

void	obj_draw_minimap(t_data *data, t_mini *mini)
{
	int			i;
	int			j;
	int			color;
	double		x;
	double		y;

	mini->start_i = data->player.pos.y - (data->mini.size >> 1) / mini->ratio;
	mini->start_j = data->player.pos.x - (data->mini.size >> 1) / mini->ratio;
	i = 0;
	while (i < mini->size)
	{
		j = 0;
		while (j < mini->size)
		{
			x = (double)j / mini->ratio + mini->start_j - data->player.pos.x;
			y = (double)i / mini->ratio + mini->start_i - data->player.pos.y;
			double rot_x = x * data->player.dir.x - y * data->player.dir.y;
			double rot_y = x * data->player.dir.y + y * data->player.dir.x;
			x = -rot_y + data->player.pos.x;
			y = rot_x + data->player.pos.y;
			color = utils_blend_color(0x000000, *(int *)(data->addr + i * data->line_length + j * (data->bpp >> 3)), 0.5);
			if (y >= 0 && y < data->map.row && x >= 0 && x < data->map.col && data->map.data[(int)y][(int)x] == '1')
				utils_draw_point(data, j, i, 0xCC0099);
			else
				utils_draw_point(data, j, i, color);
			j++;
		}
		i++;
	}
	obj_draw_mini_player(data, mini->size >> 1, 5);
}
