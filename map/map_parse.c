/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:35:01 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/04 17:32:04 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	map_error(char *msg)
{
	printf("error\n%s\n", msg);
	exit(1);
}

void	map_check_arg(int argc, char **argv)
{
	int	len;

	if (argc < 1)
		map_error("too few arguments");
	else if (argc > 1)
		map_error("too many arguments");
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + (len - 4), ".cub", 5) != 0)
		map_error("invalid extension");
}

int	*map_parse(int argc, char **argv)
{
	map_check_arg(argc, argv);
}
