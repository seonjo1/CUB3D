/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:57:08 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/10 19:08:13 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../libft_s/libft_s.h"

int	parse_tex_file(t_tex *tex, char *str, int type, int *element)
{
	if (*element & type)
		return (1);
	*element |= type;
	tex->file = ft_strdup_s(str);
	tex->file[ft_strlen(tex->file) - 1] = '\0';
	return (0);
}

void	parse_identifier_check(t_data *data, char **arr, int fd, int *element)
{
	int	flag;

	flag = 0;
	if (!arr[0] || !arr[1])
		flag = 1;
	else if (ft_strncmp(arr[0], "\n", 2) == 0)
		return ;
	else if (ft_strncmp(arr[0], "EA", 3) == 0)
		flag = parse_tex_file(&(data->tex[0]), arr[1], TX_EA, element);
	else if (ft_strncmp(arr[0], "WE", 3) == 0)
		flag = parse_tex_file(&(data->tex[1]), arr[1], TX_WE, element);
	else if (ft_strncmp(arr[0], "SO", 3) == 0)
		flag = parse_tex_file(&(data->tex[2]), arr[1], TX_SO, element);
	else if (ft_strncmp(arr[0], "NO", 3) == 0)
		flag = parse_tex_file(&(data->tex[3]), arr[1], TX_NO, element);
	else if (ft_strncmp(arr[0], "C", 2) == 0)
		flag = parse_tex_color(&(data->c_color), arr[1], TX_C, element);
	else if (ft_strncmp(arr[0], "F", 2) == 0)
		flag = parse_tex_color(&(data->f_color), arr[1], TX_F, element);
	else
		flag = 1;
	if ((flag || arr[2] != NULL) && parse_close(fd))
		parse_error("invalid map file");
}

int	parse_is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	free(line);
	return (1);
}

void	parse_texture(t_data *data, int fd)
{
	int		i;
	int		element;
	char	*line;
	char	**arr;

	element = 0;
	while (element != TX_END)
	{
		line = gnl(fd);
		if (parse_is_empty_line(line))
			continue ;
		arr = ft_split_s(line, ' ');
		parse_identifier_check(data, arr, fd, &element);
		i = 0;
		while (!arr[i])
			free(arr[i++]);
		free(arr);
		free(line);
	}
}