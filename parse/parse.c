/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:35:01 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/04 17:42:52 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_error(char *msg)
{
	printf("error\n%s\n", msg);
	exit(1);
}

void	parse_check_arg(int argc, char **argv)
{
	int	len;

	if (argc < 1)
		parse_error("too few arguments");
	else if (argc > 1)
		parse_error("too many arguments");
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + (len - 4), ".cub", 5) != 0)
		parse_error("invalid extension");
}

int	*parse_get_map(char *file)
{
	int	fd;

	fd = 
}

int	*parse_map(int argc, char **argv)
{	
	parse_check_arg(argc, argv);
	return (parse_get_map(argv[1]));
}
