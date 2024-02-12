/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:35:01 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/12 19:44:31 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

void	parse_copy_tex_data(t_tex *tex, char *addr)
{
	int	i;
	int	j;

	i = 0;
	while (i < tex->height)
	{
		j = 0;
		while (j < tex->width)
		{
			tex->data[i][j] = ((int *)addr)[(tex->width + tex->gap) * i + j];
			j++;
		}
		i++;
	}
}

void	parse_open_tex_file(t_data *data)
{
	int		i;
	int		j;
	t_tex	*tex;
	t_data	tmp;

	i = 0;
	while (i < 4)
	{
		tex = &(data->tex[i]);
		tmp.img = mlx_xpm_file_to_image(data->mlx, tex->file, \
			&(tex->width), &(tex->height));
		if (!tmp.img)
			parse_error("invalid texture file");
		tmp.addr = mlx_get_data_addr(tmp.img, &(tmp.bpp), \
			&(tmp.line_length), &(tmp.endian));
		tex->data = malloc(sizeof(int *) * tex->height);
		j = 0;
		while (j < tex->height)
			tex->data[j++] = malloc(sizeof(int) * tex->width);
		tex->gap = tmp.line_length - tex->width;
		copy_texture_data(tex, tmp.addr);
		mlx_destroy_image(data->mlx, tmp.img);
		i++;
	}
}

void	parse_map(t_data *data, int argc, char **argv)
{	
	ft_memset(&(data->map), 0, sizeof(t_map));
	parse_check_arg(argc, argv);
	parse_sizing_map(&(data->map), argv[1]);
	parse_make_map(data, argv[1]);
	parse_check_start_point(&(data->map), &(data->player));
	parse_check_wall(&(data->map));
	parse_open_tex_file(&data);
}
