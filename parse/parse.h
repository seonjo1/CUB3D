/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:35:24 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/26 15:02:25 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "../cub3d.h"

void		parse_map(t_data *data, int argc, char **argv);
void		parse_sizing_map(t_map *map, char *file);
void		parse_check_start_point(t_map *map, t_player *player);
void		parse_check_wall(t_map *map);
void		parse_error(char *msg);
int			parse_close(int fd);
void		parse_make_map(t_data *data, char *file);
void		parse_texture(t_data *data, int fd);
long long	parse_atoi(char *str);
int			parse_is_valid_line(char *line, int fd);
int			parse_tex_color(int *tex_color, char *str, int type, int *element);
void		parse_open_tex_file(t_data *data, int fd);
int			parse_tex_file(char **file, char *str, int type, int *element);

#endif