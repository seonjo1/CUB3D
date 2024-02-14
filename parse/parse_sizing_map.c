/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sizing_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:10:41 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/10 17:43:55 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	parse_sizing_line(t_map *map, char *line, int fd)
{
	int	i;
	int	col;
	int	w_flag;

	if (line == NULL)
		return (0);
	if (!parse_is_valid_line(line, fd))
		return (!map->row);
	col = 0;
	w_flag = 0;
	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		if (line[i] != ' ' && line[i] != '\n')
			w_flag = 1;
		if (w_flag)
			col++;
		i--;
	}
	free(line);
	if (col > map->col)
		map->col = col;
	map->row++;
	return (1);
}

int	parse_check_multiple_map(char *line, int fd)
{
	int	i;

	if (line == NULL)
		return (0);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != ' ')
		{
			free(line);
			parse_close(fd);
			parse_error("invalid map file");
		}
		i++;
	}
	free(line);
	return (1);
}

int	parse_count_element(char *line, int fd)
{
	int	i;

	if (!line && parse_close(fd))
		parse_error("invalid map file");
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
		{
			free(line);
			return (1);
		}
		i++;
	}
	free(line);
	return (0);
}

void	parse_sizing_map(t_map *map, char *file)
{
	int	fd;
	int	element;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		parse_error("unable to open file");
	element = 0;
	while (element < 6)
		element += parse_count_element(gnl(fd), fd);
	while (parse_sizing_line(map, gnl(fd), fd))
		;
	while (parse_check_multiple_map(gnl(fd), fd))
		;
	close(fd);
	if (map->row == 0)
		parse_error("invalid map file");
}
