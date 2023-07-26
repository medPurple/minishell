/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:02:55 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/25 23:12:06 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	expand_norme(t_binary *tree, t_env *env, int i);

void	expand(t_binary *tree, t_env *env)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (tree->data && tree->data[i])
	{
		i = expand_norme(tree, env, i);
		if (tree->data[i] == '\0')
			return ;
		if (tree->data[i] && tree->data[i] == '\"' && quotes == 0)
		{
			if (find_next_quotes(tree->data, i) == -1)
				return ;
			quotes++;
			i++;
		}
		else if (tree->data[i] && tree->data[i] == '\"' && quotes == 1)
		{
			quotes--;
			i++;
		}
		else
			i++;
	}
}

static int	expand_norme(t_binary *tree, t_env *env, int i)
{
	char	*str;

	if (tree->data[i] == '$')
	{
		if (tree->data[i + 1] == '?')
		{
			tree->status = true;
			i += 2;
		}
		else if (tree->data[i + 1] == ' ' || tree->data[i + 1] == '\0')
			i += 1;
		else
		{
			str = replace_doll_bis(tree->data, env, i + 1, 0);
			free(tree->data);
			tree->data = ft_strdup(str);
			free(str);
			i = 0;
		}
	}
	else
		i = expand_norme_2(tree, i);
	return (i);
}

char	*join_all_part(char *str, char *add)
{
	int		i;
	int		j;
	char	*before;

	i = 0;
	j = 0;
	while (str[i] != '$')
		i++;
	before = ft_malloc(i + 1, "char");
	while (j < i)
	{
		before[j] = str[j];
		j++;
	}
	before[j] = '\0';
	i++;
	while (str[i] != ' ' && str[i] != '\0' && is_letter(str[i]))
		i++;
	while (str[i] == ' ' && str[i] != '\0' && str[i] != '\t')
		i++;
	str = jap_norme(str, i, before, add);
	return (str);
}
