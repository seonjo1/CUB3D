/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:09:14 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/28 22:11:12 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/parse_bonus.h"
#include "evnt/evnt_bonus.h"
#include "rc/rc_bonus.h"
#include "play/play_bonus.h"
#include "hand/hand_bonus.h"
#include "obj/obj_bonus.h"
#include "sound/sound_bonus.h"

int	main_loop(t_data *data)
{
	void	*hand;

	play_update(data);
	rc_draw_floor(data);
	rc_draw_sky(data);
	hand = hand_update(data);
	rc_raycast(data);
	obj_draw_aim(data);
	obj_draw_minimap(data, &(data->mini));
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, hand, 1, 1);
	mlx_do_sync(data->mlx);
	data->time++;
	return (0);
}

void	main_init(t_data *data, int argc, char **argv)
{	
	ft_memset(data, 0, sizeof(t_data));
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(1);
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!data->mlx_win)
		exit(1);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
		exit (1);
	data->addr = mlx_get_data_addr(data->img, &(data->bpp),
			&(data->line_length), &(data->endian));
	if (!data->addr)
		exit(1);
	parse_map(data, argc, argv);
	hand_init_xpm_imgs(data);
	data->player.s_res = sound_init(&(data->s_res));
	obj_mini_init(data);
}

int	main(int argc, char **argv)
{
	t_data		data;

	main_init(&data, argc, argv);
	mlx_hook(data.mlx_win, 17, 0, &evnt_leave, 0);
	mlx_hook(data.mlx_win, 2, 0, &evnt_keypress, &(data.player));
	mlx_hook(data.mlx_win, 3, 0, &evnt_keyrelease, &(data.player));
	mlx_hook(data.mlx_win, 4, 0, &evnt_mousepress, &data);
	mlx_hook(data.mlx_win, 5, 0, &evnt_mouserelease, &(data.player));
	mlx_loop_hook(data.mlx, &main_loop, &data);
	mlx_loop(data.mlx);
	exit(0);
}
