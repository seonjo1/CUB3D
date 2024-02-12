/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:47:57 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/12 19:51:44 by seonjo           ###   ########.fr       */
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

void	parse_open_tex_file(t_data *data, int fd)
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
		if (!tmp.img && parse_close(fd))
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

int	parse_tex_file(t_tex *tex, char *str, int type, int *element)
{
	if (*element & type)
		return (1);
	*element |= type;
	tex->file = ft_strdup_s(str);
	tex->file[ft_strlen(tex->file) - 1] = '\0';
	return (0);
}
