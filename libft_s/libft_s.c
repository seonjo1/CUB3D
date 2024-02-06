/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:55:27 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/04 20:57:00 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_s.h"

void	*ft_calloc_s(size_t count, size_t size)
{
	void	*new;

	new = ft_calloc(count, size);
	if (!new)
		exit(1);
	return (new);
}
