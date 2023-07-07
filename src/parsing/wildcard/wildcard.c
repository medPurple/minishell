/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:55:11 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/07 15:01:54 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char *find_file(char *bfwc, char *afwc, char *begin, char *end);
static char **get_wc(char *bfwc, char *afwc,t_wc *liste);
static char *new_str(char *begin,char *end, char **tab);

char *wildcard(char *str, int i)
{
	char *bfwc;
	char *afwc;
	char *begin;
	char *end;
	int j;

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
	str = find_file(bfwc,afwc, begin, end);
	if (str == NULL)
		str = put_in_quotes(begin,end, bfwc, afwc);
	//free
	return str;
}

static char *find_file(char *bfwc, char *afwc, char *begin, char *end)
{
	(void)begin,(void)end;
	DIR *direction;
	char **tab;
	struct dirent *entry;
    struct stat statbuf;
	t_wc *liste = NULL;
	direction = opendir(getcwd(NULL,0));	
	if (direction == NULL)
		return(ft_printf("ACCESS DENIED\n"),NULL);
	while((entry = readdir(direction)) != NULL)
	{
		lstat(entry->d_name,&statbuf);
		if (entry->d_name[0] != '.')
			wc_addback(&liste,new_wc(entry->d_name));			
	}
	tab = get_wc(bfwc,afwc, liste);
	return(new_str(begin, end, tab));
}



static char **get_wc(char *bfwc, char *afwc,t_wc *liste)
{
	char **tab = NULL;
	int i;
	int j;
	int count;
	
	count = 0;
	i = 0;
	if (afwc != NULL)
		j = ft_strlen(afwc);
	if (bfwc != NULL && afwc != NULL)
		tab = wc_before_and_after(bfwc,afwc,liste);
	else if (bfwc != NULL && afwc == NULL)
		tab = wc_before(bfwc, liste);
	else if (bfwc == NULL && afwc != NULL)
		tab = wc_after(afwc, liste);
	else
		tab = wc_all(liste);
	return (tab);
}

static char *new_str(char *begin,char *end, char **tab)
{
	int i;
	char *str;
	
	i = 0;
	str = NULL;
	if (tab[0] == NULL)
		return (NULL);
	if (begin)
		str = ft_strjoat(begin, " ");
	while (tab[i])
	{
		str = ft_strjoat(str, tab[i]);
		str = ft_strjoat(str, " ");
		i++;
	}

	str = ft_strjoat(str, end);
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
	new = ft_malloc(size,"char");

	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}	

	while (*s2)
		new[i++] = *s2++;
		
	new[size] = '\0';
	return (new);
}
