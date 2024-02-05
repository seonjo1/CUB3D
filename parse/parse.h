/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:35:24 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/05 14:12:30 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "../cub3d.h"

void	parse_map(t_map *map, int argc, char **argv);
void	parse_check_map(t_map *map);
void	parse_sizing_map(t_map *map, char *file);
void	parse_error(char *msg);
int		parse_close(int fd);
void	parse_make_map(t_map *map, char *file);

#endif