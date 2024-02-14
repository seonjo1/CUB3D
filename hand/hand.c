/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:39:49 by michang           #+#    #+#             */
/*   Updated: 2024/02/14 18:39:49 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hand.h"
#include "../libft_s/libft_s.h"

void	hand_init_each(t_data *data, void **arr, int max, char *base)
{
	char	*tmp;
	char	*file_name;
	int		i;
	int		w;
	int		h;

	i = 0;
	while (i < max)
	{
		tmp = ft_itoa_s(i);
		file_name = ft_strjoin_s(base, tmp);
		free(tmp);
		tmp = file_name;
		file_name = ft_strjoin_s(file_name, ".xpm");
		free(tmp);
		arr[i] = mlx_xpm_file_to_image(data->mlx, file_name, &w, &h);
		free(file_name);
		i++;
	}
}

void	hand_init_xpm_imgs(t_data *data)
{
	hand_init_each(data, &(data->hand_res.flash), HN_FLASH, "../res/flash");
}
