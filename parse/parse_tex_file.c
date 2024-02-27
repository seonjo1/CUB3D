/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:47:57 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/27 14:41:11 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../libft_s/libft_s.h"

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

void	parse_copy_sky_tex(t_sky *tex, char *addr, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			*((int *)(tex->addr) + width * i + j) = \
				*((int *)addr + (tex->width + tex->gap) * (i * tex->height / height) + (tex->width * j) / width);
			j++;
		}
		i++;
	}
}

void	parse_open_sky_tex(t_data *data, int fd)
{
	t_sky	*tex;
	t_data	tmp;
	
	tex = &(data->sky);
	tmp.img = mlx_xpm_file_to_image(data->mlx, tex->file, \
		&(tex->width), &(tex->height));
	if (!tmp.img && parse_close(fd))
		parse_error("invalid texture file");
	tmp.addr = mlx_get_data_addr(tmp.img, &(tmp.bpp), \
		&(tmp.line_length), &(tmp.endian));
	tex->img = mlx_new_image(data->mlx, WIN_WIDTH * 3.14, WIN_HEIGHT);
	if (!(tex->img) && parse_close(fd))
		exit(1);
	tex->addr = mlx_get_data_addr(tex->img, &(tex->bpp), \
		&(tex->line_length), &(tex->endian));
	tex->gap = tmp.line_length / 4 - tex->width;
	parse_copy_sky_tex(tex, tmp.addr, tex->line_length / 4, WIN_HEIGHT);
	tex->width = WIN_WIDTH * 3.13;
	tex->height = WIN_HEIGHT;
	mlx_destroy_image(data->mlx, tmp.img);
}


void	parse_open_tex_file(t_data *data, int fd)
{
	int		i;
	int		j;
	t_tex	*tex;
	t_data	tmp;

	i = 0;
	while (i < 5)
	{
		tex = &(data->tex[i]);
		tmp.img = mlx_xpm_file_to_image(data->mlx, tex->file, \
			&(tex->width), &(tex->height));
		if (!tmp.img && parse_close(fd))
			parse_error("invalid texture file");
		tmp.addr = mlx_get_data_addr(tmp.img, &(tmp.bpp), \
			&(tmp.line_length), &(tmp.endian));
		tex->data = malloc(sizeof(int *) * tex->height);
		j = 0;
		while (j < tex->height)
			tex->data[j++] = malloc(sizeof(int) * tex->width);
		tex->gap = tmp.line_length / 4 - tex->width;
		parse_copy_tex_data(tex, tmp.addr);
		mlx_destroy_image(data->mlx, tmp.img);
		i++;
	}
	parse_open_sky_tex(data, fd);
}

int	parse_tex_file(char **file, char *str, int type, int *element)
{
	if (*element & type)
		return (1);
	*element |= type;
	*file = ft_strdup_s(str);
	(*file)[ft_strlen(*file) - 1] = '\0';
	return (0);
}
