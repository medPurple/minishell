/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_doll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:11:19 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/20 11:44:00 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
static char	*search_in_env(char *var, t_env *env, char *str);
static char *doll_quotes(char *str, int position);
static char *put_quotes(char *str, int positon);

char	*replace_doll_bis(char *str, t_env *env, int position)
{
	int	i;
	char *var;
	int j;
	
	i = 0;
	if (position >= 2)
		i = position - 2;
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '<'))
	{
		if (str[i] == '<' && str[i - 1] == '<')
		{
			return (put_quotes(str, position));
		}
		i--;
	}
	if (str[position] == '\"' || str[position] == '\'')
		return(doll_quotes(str, position));
	else
	{
		j = 0;
		i = position;
		while (str[i] != ' ' && str[i] != '\0' \
		&& is_letter(str[i]))
			i++;
		var = ft_malloc((i) - position , "char");
		while (position < i)
			var[j++] = str[position++];
		var[j] = '\0';
		return(search_in_env(var, env, str));
	}
}

bool is_letter(char c)
{
	if (c >= 'a' && c <= 'z')
		return (true);
	else if (c >= 'A' && c <= 'Z')
		return (true);
	return (false);
}
static char	*search_in_env(char *var, t_env *env, char *str)
{
	t_env	*tmp;


	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, var) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL)
		str = sie_norme(tmp, str);
	else
		str = jap_norme_2(str);
	return (str);
}

static char *doll_quotes(char *str, int position)
{
	char *bf;
	char *af;
	
	bf = NULL;
	af = NULL;
	bf = ft_limited_strdup(str, 0, position - 2);
	af = ft_limited_strdup(str, position, ft_strlen(str));
	return (ft_strjoin(bf,af));
}

static char *put_quotes(char *str, int positon)
{
	char *bf;
	char *af;
	int		i;
	
	i = positon;
	bf = ft_limited_strdup(str, 0, positon - 2);
	bf = ft_strjoat(bf, "\'");
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	af = ft_limited_strdup(str, positon - 1, i);
	af = ft_strjoat(af, "\'");
	return (ft_strjoat(bf, af));
}