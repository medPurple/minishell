/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:10:11 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/19 12:13:04 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	is_valid_bf(char *str);
static bool	has_equals(char *str);

void	mini_export(t_env **env, char **tab)
{
	t_env	*tmp;
	int		i;

	i = 1;
	while (tab[i])
	{
		if (is_valid_bf(tab[i]) == true && has_equals(tab[i]) == true)
		{
			tmp = ft_new_element(tab[i]);
			ft_add_back_lst(env, tmp);
		}
		else if (is_valid_bf(tab[i]) == true && has_equals(tab[i]) == false)
			ft_printf("");
		else
			mini_error_one(13);
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
	while (str[i] != '=' && str[i])
		i++;
	lim = ft_limited_strdup(str, 0, i - 1);
	while (lim[j])
	{
		if (!((lim[j] >= 'a' && lim[j] <= 'z') \
		|| (lim[j] >= 'A' && lim[j] <= 'Z') \
		|| (lim[j] >= '0' && lim[j] <= '9')))
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
