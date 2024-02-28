/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:11:05 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/28 21:42:10 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_error(char *msg)
{
	printf("error\n%s\n", msg);
	exit(1);
}

int	parse_close(int fd)
{
	close(fd);
	return (1);
}
