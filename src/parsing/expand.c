/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:02:55 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/17 13:46:17 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*replace_doll(char *str, t_env *env, int position);
static char	*search_in_env(char *var, t_env *env, char *str);
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
		if (tree->data && tree->data[i] == '\"' && quotes == 0)
		{
			if (find_next_quotes(tree->data, i) == -1)
				return ;
			quotes++;
			i++;
		}
		else if (tree->data && tree->data[i] == '\"' && quotes == 1)
		{
			quotes--;
			i++;
		}
	}
}

static int	expand_norme(t_binary *tree, t_env *env, int i)
{
	if (tree->data[i] == '$')
	{
		tree->data = replace_doll(tree->data, env, i + 1);
		i = 0;
	}
	else if (tree->data[i] == '*')
	{
		tree->data = wildcard(tree->data, i);
		i = 0;
	}
	else if (tree->data[i] == '\'')
		i = pass_quotes(tree->data, i) + 1;
	else
		i++;
	return (i);
}

static char	*replace_doll(char *str, t_env *env, int position)
{
	int		i;
	char	*var;

	i = position;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		i++;
	i = i - position;
	var = ft_malloc(i, "char");
	i = 0;
	while (str[position] != ' ' && str[position] != '\t'\
		&& str[position] != '\0'
		&& str[position] != '\"')
	{
		var[i] = str[position];
		i++;
		position++;
	}
	var[i] = '\0';
	str = search_in_env(var, env, str);
	return (str);
}

static char	*search_in_env(char *var, t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->data, var, ft_strlen(var)) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL)
		str = sie_norme(tmp, str);
	else
		str = jap_norme_2(str);
	return (str);
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
	while (j < i - 1)
	{
		before[j] = str[j];
		j++;
	}
	before[j] = ' ';
	before[j + 1] = '\0';
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	while (str[i] == ' ' && str[i] != '\0' && str[i] != '\t')
		i++;
	str = jap_norme(str, i, before, add);
	return (str);
}
