/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:43:54 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/28 22:01:44 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_BONUS_H
# define OBJ_BONUS_H

# include "../cub3d_bonus.h"

void	obj_draw_minimap(t_data *data, t_mini *mini);
void	obj_draw_aim(t_data *data);
void	obj_mini_init(t_data *data);

#endif