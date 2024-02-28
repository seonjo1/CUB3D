/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:37:19 by michang           #+#    #+#             */
/*   Updated: 2024/02/28 22:03:28 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_s_bonus.h"

t_vec2	vec2_creat(double x, double y)
{
	t_vec2	a;

	a.x = x;
	a.y = y;
	return (a);
}

t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	t_vec2	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

t_vec2	vec2_scala_mul(t_vec2 a, double scale)
{
	t_vec2	c;

	c.x = a.x * scale;
	c.y = a.y * scale;
	return (c);
}

t_vec2	vec2_normalize(t_vec2 vec, double scale)
{
	double	len;

	len = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (len < 0.0001)
		return (vec2_creat(0, 0));
	vec.x /= len;
	vec.y /= len;
	vec.x *= scale;
	vec.y *= scale;
	return (vec);
}
