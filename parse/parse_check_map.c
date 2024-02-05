/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:06:29 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/05 14:06:53 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	parse_is_start_point(char c)
{
	if (c == 'W' || c == 'N' || c == 'S' || c == 'E')
		return (1);
	return (0);
}

static int	parse_init_player(char c, int x, int y, t_player *player)
{
	if (!parse_is_start_point(c))
		return (0);
	player->pos.x = x;
	player->pos.y = y;
	player->dir.x = (c == 'E') - (c == 'W');
	player->dir.y = (c == 'S') - (c == 'N');
	return (1);
}

void	parse_check_start_point(t_map *map, t_player *player)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->col)
		{
			flag += parse_init_player(map->data[map->col * i + j], i, j, player);
			j++;
		}
		i++;
	}
	if (flag != 1)
		parse_error("invalid map");
}

static void parse_dfs(t_map *map, char *check, int i, int j)
{
	if (check[map->col * i + j])
		return ;
	check[map->col * i + j] = 1;
	if (map->data[map->col * i + j] == ' ')
		parse_error("invalid map");
	if (map->data[map->col * i + j] == '1')
		return ;
	if (i == 0 || i == map->row || j == 0 || j == map->col)
		parse_error("invalid map");
	parse_dfs(map, check, i - 1, j);
	parse_dfs(map, check, i + 1, j);
	parse_dfs(map, check, i, j - 1);
	parse_dfs(map, check, i, j + 1);
}

void	parse_check_wall(t_map *map)
{
	int		i;
	int		j;
	int		flag;
	char	*check;

	check = ft_calloc_s(map->row * map->col, sizeof(char));
	flag = 0;
	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->col)
		{
			if (map->data[map->col * i + j] == '0' || \
				parse_is_start_point(map->data[map->col * i + j]))
				parse_dfs(map, check, i, j);
			j++;
		}
		i++;
	}
	free(check);
}
