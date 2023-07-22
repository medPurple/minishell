/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:10:11 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/21 07:56:44 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	is_valid_bf(char *str);
static bool	has_equals(char *str);
static void	remove_last(char *str, t_env *env);

void	mini_export(t_env **env, char **tab)
{
	t_env	*tmp;
	int		i;

	i = 1;
	if (!(tab[1]))
		return (mini_env(*env));
	while (tab[i])
	{
		if (tab[i][0] == '-')
			return (mini_error_one(15));
		else if (is_valid_bf(tab[i]) == true && has_equals(tab[i]) == true)
		{
			remove_last(tab[i], *env);
			tmp = ft_new_element(tab[i]);
			ft_add_back_lst(env, tmp);
		}
		else if (is_valid_bf(tab[i]) == true && has_equals(tab[i]) == false)
			ft_printf("");
		else
			return (mini_error_one(13));
		i++;
	}
}

static bool	is_valid_bf(char *str)
{
	int		i;
	int		j;
	char	*lim;

	i = 0;
	j = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '\0' || i < 1)
		return (false);
	lim = ft_limited_strdup(str, 0, i - 1);
	while (lim[j])
	{
		if (!((lim[j] >= 'a' && lim[j] <= 'z') \
		|| (lim[j] >= 'A' && lim[j] <= 'Z') \
		|| (lim[j] >= '0' && lim[j] <= '9') \
		|| lim[j] == '_'))
			return (false);
		j++;
	}
	return (true);
}

static bool	has_equals(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

static void	remove_last(char *str, t_env *env)
{
	int		i;
	char	*name;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (str[i] != '=')
		i++;
	name = ft_limited_strdup(str, 0, i - 1);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			tmp->prev->next = tmp->next;
			free(tmp->data);
			free(tmp->name);
			free(tmp);
			break ;
		}
		tmp = tmp->next;
	}
	free(name);
}
