/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:09:14 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/08 16:00:08 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/parse.h"
#include "evnt/evnt.h"
#include "rc/rc.h"
#include "play/play.h"

void	utils_draw_point(t_data *data, int x, int y, int color)
{
	if ((x >= 0 && y >= 0) && (WIN_HEIGHT > y && WIN_WIDTH > x))
		*(int *)(data->addr + (y * data->line_length + x * (data->bpp / 8))) = color;
}

void	draw_aim(t_data *data)
{
	t_intvec2	aim;
	int			i;
	const int	aim_size = 20;

	aim.x = WIN_WIDTH / 2 - aim_size;
	aim.y = WIN_HEIGHT / 2;
	i = -1;
	while (++i < aim_size * 2)
		utils_draw_point(data, aim.x + i, aim.y, 0xFF00FF);
	aim.x = WIN_WIDTH / 2;
	aim.y = WIN_HEIGHT / 2 - aim_size;
	i = -1;
	while (++i < aim_size * 2)
		utils_draw_point(data, aim.x, aim.y + i, 0xFF00FF);
}

int	main_loop(t_data *data)
{
	clock_t start, end;

	start = clock();
	play_update(data);
	rc_raycast(data);
	draw_aim(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->hand, 0, 0);
	mlx_do_sync(data->mlx);
	data->time++;
	end = clock();
	printf("+ %.5f\n", ((double) (end - start)) / CLOCKS_PER_SEC);
	return (0);
}

void	main_init(t_data *data)
{
	int	img_width;
	int	img_height;
	
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
	data->hand = mlx_xpm_file_to_image(data->mlx, "map/hand.xpm", &img_width, &img_height);
	ft_bzero(&(data->player), sizeof(t_player));
}

int	main(int argc, char **argv)
{
	t_data		data;

	parse_map(&(data.map), &(data.player), argc, argv);
	main_init(&data);
	parse_map(&(data.map), &(data.player), argc, argv);
	printf("player init! : pos.x:%f, pos.y:%f, dir.x:%f, dir.y:%f\n", \
	data.player.pos.x, data.player.pos.y, data.player.dir.x, data.player.dir.y);
	mlx_hook(data.mlx_win, 17, 0, &evnt_leave, 0);
	mlx_hook(data.mlx_win, 2, 0, &evnt_keypress, &(data.player));
	mlx_hook(data.mlx_win, 3, 0, &evnt_keyrelease, &(data.player));
	mlx_hook(data.mlx_win, 4, 0, &evnt_mousepress, &(data.player));
	mlx_hook(data.mlx_win, 5, 0, &evnt_mouserelease, &(data.player));
	mlx_loop_hook(data.mlx, &main_loop, &data);
	mlx_loop(data.mlx);
}
