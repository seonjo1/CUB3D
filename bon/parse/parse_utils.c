/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:11:05 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/10 15:30:58 by seonjo           ###   ########.fr       */
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

long long	parse_overflow_check(long long num, long long i)
{
	if (i > 3)
		return (-1);
	if (num < 0 || num > 255)
		return (-1);
	return (num);
}

long long	parse_atoi(char *str)
{
	long long	i;
	long long	num;

	i = 0;
	num = 0;
	if (!(*str >= '0' && *str <= '9'))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
		if (num > 0)
			i++;
	}
	if (*str != '\0' && *str != '\n')
		return (-1);
	return (parse_overflow_check(num, i));
}
