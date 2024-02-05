/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:35:01 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/05 14:12:11 by seonjo           ###   ########.fr       */
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

void	parse_map(t_map *map, int argc, char **argv)
{	
	ft_memset(map, 0, sizeof(t_map));
	parse_check_arg(argc, argv);
	parse_sizing_map(map, argv[1]);
	parse_make_map(map, argv[1]);
	parse_check_map(map);
}
