/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_s.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:56:03 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/10 14:12:11 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_S_H
# define LIBFT_S_H
# include "../cub3d.h"

void	*ft_calloc_s(size_t count, size_t size);
char	**ft_split_s(const char *str, char c);
char	*ft_strdup_s(const char *s1);
char	*ft_itoa_s(int n);
char	*ft_strjoin_s(char const *s1, char const *s2);
t_vec2	vec2_creat(double x, double y);
t_vec2	vec2_add(t_vec2 a, t_vec2 b);
t_vec2	vec2_scala_mul(t_vec2 a, double b);
t_vec2	vec2_normalize(t_vec2 vec, double scale);
int		utils_blend_color(int a, int b, float op);
void	utils_draw_point(t_data *data, int x, int y, int color);
char	utils_is_in_map(int x, int y, t_map *map);

#endif