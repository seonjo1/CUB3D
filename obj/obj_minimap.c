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

	aim.x = WIN_WIDTH / 2 - aim_size;
	aim.y = WIN_HEIGHT / 2;
	i = -1;
	while (++i < aim_size * 2)
		utils_draw_point(data, aim.x + i, aim.y, 0xFF00FF);
	aim.x = WIN_WIDTH / 2;
	aim.y = WIN_HEIGHT / 2 - aim_size;
	i = -1;
	while (++i < aim_size * 2)
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
}

void	obj_draw_mini_player(t_data *data, int center, int w, int c)
{
	int	i;
	int	j;

	center = center - (w >> 1);
	center = center - (w >> 1);
	i = 0;
	while (i < w)
	{
		j = 0;
		while (j < w)
			utils_draw_point(data, center + j++, center + i, c);
		i++;
	}
}

void	obj_draw_minimap(t_data *data, t_mini *mini)
{
	int			i;
	int			j;
	int			color;
	double		x;
	double		y;

	mini->start_i = data->player.pos.y - (data->mini.size >> 1) / 6;
	mini->start_j = data->player.pos.x - (data->mini.size >> 1) / 6;
	i = 0;
	while (i < mini->size)
	{
		j = 0;
		while (j < mini->size)
		{
			x = (double)j / 6.0 + mini->start_j;
			y = (double)i / 6.0 + mini->start_i;
			color = utils_blend_color(0x000000, *(int *)(data->addr + i * data->line_length + j * (data->bpp >> 3)), 0.5);
			if (y >= 0 && y < data->map.row && x >= 0 && x < data->map.col && data->map.data[(int)y][(int)x] == '1')
				utils_draw_point(data, j, i, 0xCC0099);
			else
				utils_draw_point(data, j, i, color);
			j++;
		}
		i++;
	}
	obj_draw_mini_player(data, mini->size >> 1, 3, 0xFFFFFF);
}
