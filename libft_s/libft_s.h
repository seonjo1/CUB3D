/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_s.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:56:03 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/04 21:02:50 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_S_H
# define LIBFT_S_H
# include "../cub3d.h"

void	*ft_calloc_s(size_t count, size_t size);
t_vec2	vec2_creat(double x, double y);
t_vec2	vec2_add(t_vec2 a, t_vec2 b);
t_vec2	vec2_scala_mul(t_vec2 a, double b);
void	vec2_normalize(t_vec2 *vec, double scale);

#endif