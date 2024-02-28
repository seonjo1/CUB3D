/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_make_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:12:00 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/10 16:53:29 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../libft_s/libft_s.h"

int	parse_is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' \
		|| c == 'W' || c == 'E' || c == ' ')
		return (1);
	return (0);
}

int	parse_is_valid_line(char *line, int fd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (!parse_is_valid_char(line[i]) && parse_close(fd))
			parse_error("invalid map file");
		else if (line[i] != ' ')
			flag = 1;
		i++;
	}
	if (!flag)
		free(line);
	return (flag);
}

int	parse_fill_map(t_map *map, char *line, int fd, int *row)
{
	int	i;
	int	w_flag;

	if (line == NULL)
		return (0);
	if (!parse_is_valid_line(line, fd))
		return (!(*row));
	w_flag = 0;
	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		if (line[i] != ' ' && line[i] != '\n')
			w_flag = 1;
		if (w_flag)
			map->data[*row][i] = line[i];
		i--;
	}
	i = map->col - 1;
	while (!map->data[*row][i])
		map->data[*row][i--] = ' ';
	free(line);
	(*row)++;
	return (1);
}

void	parse_make_map(t_data *data, char *file)
{
	int	i;
	int	fd;
	int	row;

	data->map.data = ft_calloc_s(data->map.row, sizeof(char *));
	i = 0;
	while (i < data->map.row)
		data->map.data[i++] = ft_calloc_s(data->map.col, sizeof(char));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		parse_error("unable to open file");
	parse_texture(data, fd);
	row = 0;
	while (parse_fill_map(&(data->map), gnl(fd), fd, &row))
		;
	parse_close(fd);
}
