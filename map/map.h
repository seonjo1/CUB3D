/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:35:24 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/04 17:27:26 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../cub3d.h"
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"

int	*map_parse(int argc, char **argv);

#endif