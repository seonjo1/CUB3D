/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:59:24 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/28 20:51:24 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RC_H
# define RC_H
# include "../cub3d.h"

void	rc_get_distance(t_data *data, t_rc_data *rc_data, \
	t_draw_data *d_data, t_vec2 ray);
void	rc_raycast(t_data *data);

#endif