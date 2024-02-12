/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:07:27 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/12 19:59:15 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../libft_s/libft_s.h"

int	parse_comma_check(char *str)
{
	int	i;
	int	comma_num;

	i = 0;
	comma_num = 0;
	while (str[i])
	{
		if (str[i++] == ',')
			comma_num++;
	}
	if (comma_num == 2)
		return (0);
	else
		return (1);
}

int	parse_get_color(char **arr)
{
	int	i;
	int	num;
	int	color;

	i = 0;
	color = 0;
	while (arr[i])
	{
		num = parse_atoi(arr[i]);
		if (num == -1)
			return (-1);
		color = (color << 8) | num;
		i++;
	}
	return (color);
}

int	parse_color_check(char *str)
{
	char	**arr;
	int		i;
	int		color;

	arr = ft_split_s(str, ',');
	color = parse_get_color(arr);
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	if (color == -1 || i != 3)
		return (-1);
	else
		return (color);
}

int	parse_tex_color(int *tex_color, char *str, int type, int *element)
{
	int	input_color;

	if (*element & type)
		return (1);
	*element |= type;
	if (parse_comma_check(str))
		return (1);
	input_color = parse_color_check(str);
	if (input_color == -1)
		return (1);
	*tex_color = input_color;
	return (0);
}
