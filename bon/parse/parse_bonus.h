/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:35:24 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/28 22:01:44 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H
# include "../cub3d_bonus.h"

void		parse_map(t_data *data, int argc, char **argv);
void		parse_sizing_map(t_map *map, char *file);
void		parse_check_start_point(t_map *map, t_player *player);
void		parse_check_wall(t_map *map);
void		parse_error(char *msg);
int			parse_close(int fd);
void		parse_make_map(t_data *data, char *file);
void		parse_texture(t_data *data, int fd);
int			parse_is_valid_line(char *line, int fd);
void		parse_open_tex_file(t_data *data, int fd);
int			parse_tex_file(char **file, char *str, int type, int *element);

#endif