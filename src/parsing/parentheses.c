/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:03:06 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/19 10:16:27 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ignore_parentheses(t_binary *tree)
{
	int	i;
	int	para_count;

	i = 1;
	para_count = 1;
	while (para_count != 0)
	{
		if (tree->data[i] == '\0')
			break ;
		if (tree->data[i] == ')')
			para_count--;
		else if (tree->data[i] == '(')
			para_count++;
		i++;
	}
	while ((is_a_meta(tree->data, i) != true) && tree->data[i])
		i++;
	if (i != (int)ft_strlen(tree->data))
	{
		tree->command = ft_limited_strdup(tree->data, 0, i - 1);
		tree->rest = ft_limited_strdup(tree->data, i, ft_strlen(tree->data));
	}
	else
		tree->parentheses = true;
	return ;
}

int	end_of_parentheses(char *str, int position)
{
	int	i;
	int	para_count;

	i = position + 1;
	para_count = 1;
	while (para_count != 0 && str[i])
	{
		if (str[i] == '\0')
			break ;
		if (str[i] == ')')
			para_count--;
		else if (str[i] == '(')
			para_count++;
		i++;
	}
	return (i);
}

int	verif_parentheses(t_binary *tree)
{
	int	i;

	if (tree->parentheses == 1)
	{
		i = 0;
		while (tree->data[i] != '(')
			i++;
		i = end_of_parentheses(tree->data, i);
		while (tree->data[i] == ' ' || tree->data[i] != '\0')
			i++;
		if (i != (int)ft_strlen(tree->data))
			return (-1);
	}
	if (tree->right)
	{
		if (verif_parentheses(tree->left) == -1)
			return (-1);
		verif_parentheses(tree->right);
	}
	return (0);
}
