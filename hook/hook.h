/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:36:21 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/08 16:00:32 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
# define HOOK_H
# include "../cub3d.h"

int	keypress_event(int keycode, t_data *data);
int	leave_event(t_data *data);

#endif