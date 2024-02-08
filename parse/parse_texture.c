/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:57:08 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/08 22:05:14 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_open_texture(int **tex, char *arr, int type, int *element)
{
	if (*element & type)
		return (1);
	*element |= type;

}

int	parse_dot_check(char *line)
{
	int	i;
	int	dot_num;

	i = 0;
	dot_num = 0;
	while (line[i])
	{
		if (line[i++] == '.')
			dot_num++;
	}
	if (dot_num == 2)
		return (0);
	else
		return (1);
}

int	parse_color_check(char *line)
{
	char	**arr;
	int		i;
	int		num;
	int		color;
	int		flag;

	arr = ft_split_s(line, '.');
	i = 0;
	flag = 0;
	while (arr[i])
	{
		num = parse_atoi(arr[0]);
		if (num == -1)
		{
			flag = 1;
			break ;
		}
		color = (color << 6) | num;
		i++;
	}
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	if (i == 3)
		return (color);
	else
		return (-1);
}

int	parse_color(int *tex_color, char *arr, int type, int *element)
{
	int	input_color;

	if (*element & type)
		return (1);
	*element |= type;
	if (parse_dot_check(arr))
		return (1);
	input_color = parse_color_check(arr);
	if (input_color == -1)
		return (1);
	*tex_color = input_color;
	return (0);
}

void	parse_identifier_check(t_map *map, char **arr, int fd, int *element)
{
	int	flag;

	flag = 0;
	if (ft_strncmp(arr[0], "\n", 2) == 0)
		return ;
	else if (!arr[1])
		flag = 1;
	else if (ft_strncmp(arr[0], "NO", 3) == 0)
		flag = parse_open_texture(map->NO, arr[1], TX_NO, *element);
	else if (ft_strncmp(arr[0], "SO", 3) == 0)
		flag = parse_open_texture(map->SO, arr[1], TX_SO, *element);
	else if (ft_strncmp(arr[0], "WE", 3) == 0)
		flag = parse_open_texture(map->WE, arr[1], TX_WE, *element);
	else if (ft_strncmp(arr[0], "EA", 3) == 0)
		flag = parse_open_texture(map->EA, arr[1], TX_EA, *element);
	else if (ft_strncmp(arr[0], "F", 2) == 0)
		flag = parse_open_texture(map->F, arr[1], TX_F, *element);
	else if (ft_strncmp(arr[0], "C", 2) == 0)
		flag = parse_open_texture(map->C, arr[1], TX_C, *element);
	else
		flag = 1;
	if ((flag || arr[2] != NULL) && parse_close(fd))
		parse_error("invalid map file");
}

void	parse_texture(t_map *map, int fd)
{
	int		i;
	int		element;
	char	*line;
	char	**arr;

	element = 0;
	while (element != TX_END)
	{
		line = gnl(fd);
		arr = ft_split_s(line, ' ');
		parse_identifier_check(map, arr, fd, &element);
		i = 0;
		while (!arr[i])
			free(arr[i++]);
		free(arr);
		free(line);
	}
}