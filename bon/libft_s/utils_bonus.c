/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:16:52 by michang           #+#    #+#             */
/*   Updated: 2024/02/28 22:03:28 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_s_bonus.h"

void	utils_draw_point(t_data *data, int x, int y, int c)
{
	if (!((x >= 0 && y >= 0) && (WIN_HEIGHT > y && WIN_WIDTH > x)))
		return ;
	*(int *)(data->addr + (y * data->line_length + x * (data->bpp >> 3))) = c;
}

int	utils_blend_color(int c1, int c2, float op)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((c1 >> 16) & 0xFF) * op + ((c2 >> 16) & 0xFF) * (1 - op));
	g = (int)(((c1 >> 8) & 0xFF) * op + ((c2 >> 8) & 0xFF) * (1 - op));
	b = (int)((c1 & 0xFF) * op + (c2 & 0xFF) * (1 - op));
	return ((r << 16) | (g << 8) | b);
}

char	utils_is_in_map(int x, int y, t_map *map)
{
	return (x >= 0 && y >= 0 && x < map->col && y < map->row);
}
