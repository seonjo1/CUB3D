/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:06:29 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/08 20:13:23 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../libft_s/libft_s.h"

static int	parse_init_player(char **data, int y, int x, t_player *player)
{
	if (!(data[y][x] == 'W' || data[y][x] == 'N'
		|| data[y][x] == 'S' || data[y][x] == 'E'))
		return (0);
	player->pos.x = x;
	player->pos.y = y;
	player->euler_dir.y += 90 * (data[y][x] == 'S');
	player->euler_dir.y += 180 * (data[y][x] == 'W');
	player->euler_dir.y += 270 * (data[y][x] == 'N');
	player->fov = FOV_BASE;
	player->euler_dir.y *= M_PI / 180.0;
	player->recall.cooldown = RECALL_COOLDOWN;
	ft_strlcpy(player->state, "W__", 4);
	data[y][x] = '0';
	return (1);
}

void	parse_check_start_point(t_map *map, t_player *player)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = -1;
	while (++i < map->row)
	{
		j = -1;
		while (++j < map->col)
			flag += parse_init_player(map->data, i, j, player);
	}
	if (flag != 1)
		parse_error("invalid map file");
}

static void	parse_dfs(t_map *map, char **check, int i, int j)
{
	if (check[i][j])
		return ;
	check[i][j] = 1;
	if (map->data[i][j] == ' ')
		parse_error("invalid map file");
	if (map->data[i][j] == '1')
		return ;
	if (i == 0 || i == map->row - 1 || j == 0 || j == map->col - 1)
		parse_error("invalid map file");
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
	char	**check;

	check = ft_calloc_s(map->row, sizeof(char *));
	i = 0;
	while (i < map->row)
		check[i++] = ft_calloc_s(map->col, sizeof(char));
	flag = 0;
	i = -1;
	while (++i < map->row)
	{
		j = -1;
		while (++j < map->col)
		{
			if (map->data[i][j] == '0')
				parse_dfs(map, check, i, j);
		}
	}
	i = 0;
	while (i < map->row)
		free(check[i++]);
	free(check);
}
