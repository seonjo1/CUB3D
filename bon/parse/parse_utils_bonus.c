/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:11:05 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/28 22:03:55 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_bonus.h"

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
