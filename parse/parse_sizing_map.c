/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sizing_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:10:41 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/10 15:51:05 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	parse_is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' \
		|| c == 'W' || c == 'E' || c == ' ' || c == '\n')
		return (1);
	return (0);
}

int	parse_sizing_line(t_map *map, char *line, int fd)
{
	int	i;
	int	col;
	int	is_valid_line;

	if (line == NULL)
		return (0);
	col = 0;
	is_valid_line = 0;
	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		if (!parse_is_valid_char(line[i]) && parse_close(fd))
			parse_error("invalid map file");
		else if (line[i] != ' ' && line[i] != '\n')
			is_valid_line = 1;
		if (is_valid_line)
			col++;
		i--;
	}
	free(line);
	if (!is_valid_line && map->row != 0)
		return (0);
	else if (is_valid_line)
	{
		if (col > map->col)
			map->col = col;
		map->row++;
	}
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
		if (line[i] != ' ' || line[i] != '\n')
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
