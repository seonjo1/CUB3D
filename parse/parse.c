/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:35:01 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/04 21:10:12 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_error(char *msg)
{
	printf("error\n%s\n", msg);
	exit(1);
}

void	parse_check_arg(int argc, char **argv)
{
	int	len;

	if (argc < 2)
		parse_error("too few arguments");
	else if (argc > 2)
		parse_error("too many arguments");
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + (len - 4), ".cub", 5) != 0)
		parse_error("invalid extension");
}

int	parse_is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || \
		c == 'S' || c == 'W' || c == 'E' || c == ' ')
		return (1);
	return (0);
}

int	parse_close(int fd)
{
	close(fd);
	return (1);
}

int	parse_sizing_line(t_map *map, char *line, int fd)
{
	int	i;
	int	is_valid_line;

	if (line == NULL)
		return (0);
	i = 0;
	is_valid_line = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (!parse_is_valid_char(line[i]) && parse_close(fd))
			parse_error("invalid map");
		else if (line[i] != ' ')
			is_valid_line = 1;
		i++;
	}
	free(line);
	if (!is_valid_line && map->row != 0)
		return (0);
	else if (is_valid_line)
	{
		if (map->col < i)
			map->col = i;
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
			parse_error("invalid map");
		}
		i++;
	}
	free(line);
	return (1);
}

void	parse_get_map_size(t_map *map, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		parse_error("unable to open file");
	while (parse_sizing_line(map, gnl(fd), fd))
		;
	while (parse_check_multiple_map(gnl(fd), fd))
		;
	close(fd);
}

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
		map->data[*col * map->col + i] = line[i];
		i++;
	}
	while (i < map->col)
		map->data[*col * map->col + i++] = ' ';
	free(line);
	if (!is_valid_line && (*col))
		return (0);
	else if (is_valid_line)
		(*col)++;
	return (1);
}

void	parse_make_map(t_map *map, char *file)
{
	int	fd;
	int	col;

	map->data = ft_calloc_s(map->row * map->col, sizeof(int));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		parse_error("unable to open file");
	col = 0;
	while (parse_fill_map(map, gnl(fd), &col))
		;
	parse_close(fd);
}

// void	print_map(t_map *map)
// {
// 	for (int i = 0; i < map->row; i++)
// 	{
// 		for(int j = 0; j < map->col; j++)
// 			printf("%c ", map->data[map->col * i + j]);
// 		printf("\n");
// 	}	
// }

void	parse_map(t_map *map, int argc, char **argv)
{	
	ft_memset(map, 0, sizeof(t_map));
	parse_check_arg(argc, argv);
	parse_get_map_size(map, argv[1]);
	printf("row : %d, col : %d\n", map->row, map->col);
	parse_make_map(map, argv[1]);
	// print_map(map);
	// parse_check_map(map);
}
