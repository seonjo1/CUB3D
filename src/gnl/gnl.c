/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:52:45 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/04 16:27:24 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl(int fd)
{
	int		flag;
	char	*line;

	flag = 0;
	line = get_next_line(fd, &flag);
	if (flag == 1)
		exit(1);
	return (line);
}
