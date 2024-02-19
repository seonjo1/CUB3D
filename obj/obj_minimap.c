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

void	obj_mini_init(t_data *data)
{
	if (WIN_WIDTH > WIN_HEIGHT)
		data->mini.size = WIN_HEIGHT / 5;
	else
		data->mini.size = WIN_WIDTH / 5;
	if (!(data->mini.size % 2))
		data->mini.size += 1;
	data->mini.img = mlx_new_image(data->mlx, data->mini.size, data->mini.size);
	if (!data->mini.img)
		exit(1);
	data->mini.addr = mlx_get_data_addr(data->mini.img, &(data->mini.bpp), &(data->mini.line_length), &(data->mini.endian));
	if (!data->mini.addr)
		exit(1);
}

void	obj_draw_minimap(t_data *data, t_mini *mini)
{
	int		i;
	int		j;
	double	x;
	double	y;

	mini->start_i = data->player.pos.y - (data->mini.size / 2) / 6;
	mini->start_j = data->player.pos.x - (data->mini.size / 2) / 6;
	i = 0;
	while (i < mini->size)
	{
		j = 0;
		while (j < mini->size)
		{
			x = (double)j / 6.0 + mini->start_j;
			y = (double)i / 6.0 + mini->start_i;
			if (y >= 0 && y < data->map.row && x >= 0 && x < data->map.col && data->map.data[(int)y][(int)x] == '1')
				*(int *)(mini->addr + i * mini->line_length + j * (mini->bpp / 8)) = 0xCC0099;
			else
				*(int *)(mini->addr + i * mini->line_length + j * (mini->bpp / 8)) = 0xCC000000;
			j++;
		}
		i++;
	}
	*(int *)(mini->addr + (mini->size / 2) * mini->line_length + (mini->size / 2) * (mini->bpp / 8)) = 0xffffff;
}