/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:27:49 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/22 13:28:14 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_malloc(int size, char *type)
{
	char	*str;

	if (ft_strcmp(type, "char") == 0)
	{
		str = malloc(sizeof (char) * size + 1);
		if (!str)
			return (NULL);
	}
	else if (ft_strcmp(type, "int") == 0)
	{
		str = malloc(sizeof (int) * size + 1);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	**ft_malloc2(int size, char *type)
{
	char	**str;

	if (ft_strcmp(type, "char*") == 0)
	{
		str = malloc(sizeof (char *) * (size + 1));
		if (!str)
			return (NULL);
	}
	return (str);
}
