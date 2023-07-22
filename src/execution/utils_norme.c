/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_norme.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:58:21 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/22 16:53:06 by mvautrot         ###   ########.fr       */
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
