/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:11:05 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/08 21:28:51 by seonjo           ###   ########.fr       */
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

char	*parse_sign_check(char *str, long long *minus)
{
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*minus = *minus * -1;
		str++;
	}
	return (str);
}

long long	parse_overflow_check(long long num, long long i)
{
	if (i > 10)
		return (-1);
	if (num < 0 || num > 2147483647)
		return (-1);
	return (num);
}

long long	parse_atoi(char *str)
{
	long long	minus;
	long long	i;
	long long	num;

	i = 0;
	num = 0;
	minus = 1;
	while (*str >= 9 && *str <= 13)
		str++;
	str = parse_sign_check(str, &minus);
	if (!(*str >= '0' && *str <= '9'))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
		if (num > 0)
			i++;
	}
	if (*str != '\0')
		return (-1);
	return (parse_overflow_check(num * minus, i));
}