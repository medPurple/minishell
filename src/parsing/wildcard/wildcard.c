/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:55:11 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/26 15:50:45 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*find_file(char *bfwc, char *afwc, char *begin, char *end);
static char	**get_wc(char *bfwc, char *afwc, t_wc *liste);
static char	*new_str(char *begin, char *end, char **tab);

char	*wildcard(char *str, int i)
{
	char	*bfwc;
	char	*afwc;
	char	*begin;
	char	*end;
	int		j;

	j = i;
	while (str[j] != ' ' && str[j] != '\t' && str[j])
		j--;
	bfwc = ft_limited_strdup(str, j + 1, i - 1);
	begin = ft_limited_strdup(str, 0, j - 1);
	j = i;
	while (str[j] != ' ' && str[j] != '\t' && str[j])
		j++;
	afwc = ft_limited_strdup(str, i + 1, j - 1);
	end = ft_limited_strdup(str, j, ft_strlen(str) - 1);
	str = find_file(bfwc, afwc, begin, end);
	if (str == NULL)
		str = put_in_quotes(begin, end, bfwc, afwc);
	return (str);
}

static char	*find_file(char *bfwc, char *afwc, char *begin, char *end)
{
	DIR				*direction;
	struct dirent	*entry;
	struct stat		statbuf;
	t_wc			*liste;
	t_wc			*tmp;

	liste = NULL;
	direction = opendir(getcwd(NULL, 0));
	if (direction == NULL)
		return (mini_error_one(12), NULL);
	entry = readdir(direction);
	while (entry != NULL)
	{
		lstat(entry->d_name, &statbuf);
		if (entry->d_name[0] != '.')
		{
			tmp = new_wc(ft_strdup(entry->d_name));
			wc_addback(&liste, tmp);
		}
		entry = readdir(direction);
	}
	closedir(direction);
	return (new_str(begin, end, get_wc(bfwc, afwc, liste)));
}

static char	**get_wc(char *bfwc, char *afwc, t_wc *liste)
{
	char	**tab;

	tab = NULL;
	if (bfwc != NULL && afwc != NULL)
		tab = wc_before_and_after(bfwc, afwc, liste);
	else if (bfwc != NULL && afwc == NULL)
		tab = wc_before(bfwc, liste);
	else if (bfwc == NULL && afwc != NULL)
		tab = wc_after(afwc, liste);
	else
		tab = wc_all(liste);
	ft_free_wc(liste);
	if (!tab[0])
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}

static char	*new_str(char *begin, char *end, char **tab)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	if (!tab || tab[0] == NULL)
		return (NULL);
	if (begin)
		str = ft_strjoin(begin, " ");
	while (tab[i])
	{
		str = ft_strjoin(str, tab[i]);
		str = ft_strjoin(str, " ");
		i++;
	}
	str = ft_strjoat(str, end);
	ft_free_tab(tab);
	return (str);
}

char	*ft_strjoat(char *s1, char *s2)
{
	char	*new;
	int		size;
	int		i;

	i = 0;
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	size = (ft_strlen(s1) + ft_strlen(s2));
	new = ft_malloc(size, "char");
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}	
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (free(s1), free(s2), new);
}
