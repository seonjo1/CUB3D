/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:35:01 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/04 17:16:24 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	map_check_arg(int argc, char **argv)
{
	int len;
	
	if (argc < 1)
	{
		printf("erron\nToo few arguments\n");
		exit(1);
	}
	else if (argc > 1)
	{
		printf("erron\nToo many arguments\n");
		exit(1);
	}
	len = ft_strlen(argv[1]);
	if (len )
}

int	*map_parse(int argc, char **argv)
{
	map_check_arg(argc, argv);
}
