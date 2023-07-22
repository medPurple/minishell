/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_norme.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:58:21 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/22 15:19:03 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verif_redir_norme(t_binary *tree)
{
	if (tree->right)
	{
		if (verif_redir(tree->left, 0, 0, 0) == -1)
			return (-1);
		if (verif_redir(tree->right, 0, 0, 0) == -1)
			return (-1);
	}
	return (0);
}

bool	count_space_pipe(char *str, int pos)
{
	int	i;

	if (pos > (int)ft_strlen(str))
		return (true);
	if (str[pos] && str[pos + 1] && str[pos + 2])
		i = pos + 1;
	else
		i = pos;
	while (str[i] && str[i] != '|')
	{
		ft_printf("str[i]  %c\n", str[i]);
		if (str[i] != ' ' && str[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}
