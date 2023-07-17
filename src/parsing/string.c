/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:00:12 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/17 11:55:11 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	split_char(t_binary *tree)
{
	int		i;
	char	c;

	i = 0;
	c = tree->data[0];
	while (tree->data[i] == c)
		i++;
	tree->command = ft_limited_strdup(tree->data, 0, i - 1);
	tree->rest = ft_limited_strdup(tree->data, i + 1, ft_strlen(tree->data));
}

int	find_next_split(t_binary *tree, t_env *env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (tree->data[i] != '\0')
	{
		i = ipp_norme_2(tree->data, i);
		i = fns_norme(tree->data, i);
		str = ft_limited_strdup(tree->data, j, i - 1);
		if (string_analyse(str, env) != true)
		{
			free(str);
			while ((tree->data[i] == ' ' || tree->data[i] == '\t') \
				&& tree->data[i] != '\0')
				i++;
			j = i;
		}
		else
			return (split_pos(tree->data, i - 2));
		if (tree->data[i] == '\0')
			return (-1);
	}
	return (-1);
}

bool	string_analyse(char *str, t_env *env)
{
	int	i;

	i = 0;
	if (is_a_fonction(str, env) || is_a_buildin(str))
		return (false);
	else
	{
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				i = end_of_quotes(str, i);
			else if (str[i] == '(')
				i = end_of_parentheses(str, i);
			else
			{
				if (is_a_meta(str, i) == true)
					return (true);
				i++;
			}
		}
		return (false);
	}
}

int	split_pos(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = end_of_quotes(str, i);
		else if (str[i] == '(')
			i = end_of_parentheses(str, i);
		else
		{
			if ((is_a_meta(str, i) == true))
			{
				return (i - 1);
			}
			i++;
		}
	}
	return (-1);
}

bool	has_nothing(char *str)
{
	int	i;

	i = 0;
	while (str && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '\0')
		return (true);
	return (false);
}
