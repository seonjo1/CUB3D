/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_make_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:12:00 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/05 19:56:00 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	parse_fill_map(t_map *map, char *line, int *col)
{
	int	i;
	int	is_valid_line;

	if (line == NULL)
		return (0);
	i = 0;
	is_valid_line = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != ' ')
			is_valid_line = 1;
		map->data[*col][i] = line[i];
		i++;
	}
	while (i < map->col)
		map->data[*col][i++] = ' ';
	free(line);
	if (!is_valid_line && (*col))
		return (0);
	else if (is_valid_line)
		(*col)++;
	return (1);
}

void	parse_make_map(t_map *map, char *file)
{
	int	i;
	int	fd;
	int	col;

	map->data = ft_calloc_s(map->row, sizeof(char *));
	i = 0;
	while (i < map->row)
		map->data[i++] = ft_calloc_s(map->col, sizeof(char));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		parse_error("unable to open file");
	col = 0;
	while (parse_fill_map(map, gnl(fd), &col))
		;
	parse_close(fd);
}
