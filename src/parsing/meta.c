/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:58:12 by mvautrot          #+#    #+#             */
/*   Updated: 2023/05/30 13:58:19 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ignore_parentheses(t_binary *tree)
{
	int i = 1;
	int para_count = 1;

	while (para_count != 0)
	{
		if (tree->data[i] == '\0')
			break;
		if (tree->data[i] == ')')
			para_count--;
		else if (tree->data[i] == '(')
			para_count++;
		i++;
	}
	if (i != (int)ft_strlen(tree->data))
	{
		tree->command = ft_limited_strdup(tree->data, 0, i);
		tree->rest = ft_limited_strdup(tree->data, i+1, ft_strlen(tree->data));
	} else
		return;
}

int end_of_quotes(char *str, int i)
{
	char c;

	c = str[i];
	i++;
	while (str[i] != c)
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
		else
			i++;
	}
	i++;
	while (is_a_meta(str[i]) != true)
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
		else
			i++;
	}
	return (i);

}

bool is_a_meta(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (true);
	else
		return (false);
}

int pass_quotes(char *str, int i)
{
	char c;

	c = str[i];
	while(str[i] != c)
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
		i++;
	}
	return (i);
}
