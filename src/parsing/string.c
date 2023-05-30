/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:00:12 by mvautrot          #+#    #+#             */
/*   Updated: 2023/05/30 14:02:25 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void split_char(t_binary *tree)
{
	int i;

	i = 0;
	while (is_a_meta(tree->data[i]) == true)
		i++;
	tree->command = ft_limited_strdup(tree->data,0,i);
	tree->rest = ft_limited_strdup(tree->data,i+1, ft_strlen(tree->data));
}

int find_next_split(t_binary *tree, t_env *env)
{
	int i = 0;
	int j = 0;
	char *str;

	while(tree->data[i] != '\0')
	{

		while(tree->data[i] != '\0' && tree->data[i] != ' ' && tree->data[i] != '\t')
		{
			if (tree->data[i] == '\'' || tree->data[i] == '\"')
				i = end_of_quotes(tree->data, i);
			else
				i++;
		}
		str = ft_limited_strdup(tree->data, j, i - 1);
		if (string_analyse(str,env) != true)
		{
			free(str);
			while ((tree->data[i] == ' ' || tree->data[i] == '\t') && tree->data[i] != '\0')
				i++;
			j = i;
		} else
		{
			if (j == 0 && (is_a_fonction(str, env) || is_a_buildin(str))) {
				free(str);
				while ((tree->data[i] == ' ' || tree->data[i] == '\t') && tree->data[i] != '\0')
					i++;
				j = i;
			}
			else
				return(split_pos(tree->data, env, j, i - 1));
		}

		if (tree->data[i] == '\0')
			return (-1);
	}
	return (-1);
}

bool string_analyse(char *str, t_env *env)
{
	int i = 0;

	if (is_a_fonction(str, env) || is_a_buildin(str))
		return(true);
	else
	{
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				i = end_of_quotes(str, i);
			else{
				if((str[i]) == '(' || str[i] == '&' || str[i] == '|' || str[i] == '<' || str[i] == '>')
					return (true);
				i++;
			}
		}
		return(false);
	}
}

int split_pos(char *str, t_env *env, int j, int i)
{
	char *str_a = ft_limited_strdup(str, j, i);
	if (is_a_fonction(str_a, env) || is_a_buildin(str_a))
	{
		return(j - 1);
	}
	else
	{
		i = j;
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				i = end_of_quotes(str, i);
				return (i - 1);
			}
			else {
				if ((str[i]) == '(' || str[i] == '&' || str[i] == '|' || str[i] == '<' || str[i] == '>')
					return (i - 1);
				i++;
			}
		}
	}
	return (-1);
}
