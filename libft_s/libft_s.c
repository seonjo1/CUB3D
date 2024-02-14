/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:55:27 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/10 14:12:04 by seonjo           ###   ########.fr       */
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

char	**ft_split_s(const char *str, char c)
{
	char	**new;

	new = ft_split(str, c);
	if (!new)
		exit(1);
	return (new);
}

char	*ft_strdup_s(const char *s1)
{
	char	*new;

	new = ft_strdup(s1);
	if (!new)
		exit(1);
	return (new);
}

char	*ft_itoa_s(int n)
{
	char	*new;

	new = ft_itoa(n);
	if (!new)
		exit(1);
	return (new);
}

char	*ft_strjoin_s(char const *s1, char const *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (!new)
		exit(1);
	return (new);
}
