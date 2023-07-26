/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_strchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:06:22 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/26 17:18:22 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

bool	ft_d_strchr(char *str, char *chr)
{
	int	i;
	int	j;
	int	k;

	i = ft_strlen(chr);
	j = 0;
	k = 0;
	while (str[j])
	{
		while (str[j] && str[j] == chr[k] && k <= i)
		{
			if (k == i)
				return (true);
			k++;
			j++;
		}
		k = 0;
		j++;
	}
	return (false);
}
