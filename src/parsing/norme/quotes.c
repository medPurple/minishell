/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:16:31 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/22 17:27:16 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*rmq_norme(char *tab)
{
	int		i;
	int		j;
	char	*nstr;

	i = 0;
	j = 0;
	nstr = ft_malloc(ft_strlen(tab) - 2, "char");
	while (tab[i])
	{
		if (!(tab[i] == '\'' || tab[i] == '\"'))
			nstr[j++] = tab[i++];
		else
		{
			if (tab[i + 1])
				i++;
			else
			{
				nstr[j] = '\0';
				return (nstr);
			}
		}
	}
	nstr[j] = '\0';
	return (nstr);
}

int	verif_quotes(t_binary *tree)
{
	int	i;

	i = 0;
	if (!(tree->right))
	{
		while (tree->data[i])
		{
			if (tree->data[i] == '\'' || tree->data[i] == '\"')
			{
				i = pass_quotes(tree->data, i);
				if (tree->data[i] == '\0')
					return (-1);
			}
			i++;
		}
	}
	if (tree->right)
	{
		if (verif_quotes(tree->left) == -1)
			return (-1);
		if (verif_quotes(tree->right) == -1)
			return (-1);
	}
	return (0);
}
