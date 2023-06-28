/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:55:11 by wmessmer          #+#    #+#             */
/*   Updated: 2023/06/22 11:41:57 by wmessmer         ###   ########.fr       */
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
	end = ft_limited_strdup(str, j, ft_strlen(str));
	str = find_file(bfwc,afwc, begin, end);
	ft_printf("[New str] %s\n",str);
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
	for (int k = 0; tab[k];k++)
		ft_printf("%s\n",tab[k]);
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
	str = ft_strjoin(begin, " ");
	while (tab[i])
	{
		str = ft_strjoin(str, tab[i]);
		str = ft_strjoin(str, " ");
		i++;
	}
	str = ft_strjoin(str, end);
	return (str);
}