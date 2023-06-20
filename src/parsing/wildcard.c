/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:55:11 by wmessmer          #+#    #+#             */
/*   Updated: 2023/06/20 16:57:50 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static char *find_file(char *bfwc, char *afwc, char *begin, char *end);
static void wc_addback(t_wc **list, t_wc *new);
static t_wc *new_wc(char *str);

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
	ft_printf("[Wildcard] bfwc : %s | atwc : %s\n[STR] Before : %s | After : %s\n", bfwc, afwc,begin, end); // ce qu'il y a avant et apres la wc
	str = find_file(bfwc,afwc, begin, end);
	ft_printf("[New str] %s\n",str);
	exit(0);
	return str;
}

static char *find_file(char *bfwc, char *afwc, char *begin, char *end)
{
	(void)bfwc,(void)afwc,(void)begin,(void)end;
	DIR *direction;
	struct dirent *entry;
    struct stat statbuf;
	t_wc *liste;
	direction = opendir(getcwd(NULL,0));	
	if (direction == NULL)
		return(ft_printf("ACCESS DENIED\n"),NULL);
	while((entry = readdir(direction)) != NULL)
	{
		lstat(entry->d_name,&statbuf);
		wc_addback(&liste,new_wc(entry->d_name));
		ft_printf("[File] %s\n",entry->d_name);
	}
	while(liste != NULL)
	{
		ft_printf("[File] %s\n",liste->file);
		liste = liste->next;
	}
	return("ok");
}

static void wc_addback(t_wc **list, t_wc *new)
{
	t_wc	*tmp;

	if (!(*list))
	{
		ft_printf("NOK");
		*list = new;
	}
		
	else
	{
		tmp = (*list);
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		ft_printf("Ok");
	}
}

static t_wc *new_wc(char *str)
{
	t_wc	*element;

	element = (t_wc *)malloc(sizeof(t_wc));
	if (!(element))
		return (NULL);
	element->file = str;
	element->next = NULL;
	return (element);
}