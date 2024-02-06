/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:37:19 by michang           #+#    #+#             */
/*   Updated: 2024/02/06 13:37:20 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_s.h"

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

t_vec2	vec2_scala_mul(t_vec2 a, double b)
{
	t_vec2	c;

	c.x = a.x * b;
	c.y = a.y * b;
	return (c);
}
