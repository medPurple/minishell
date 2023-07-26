/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:03:19 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/26 15:54:25 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**wc_before_and_after(char *bfwc, char *afwc, t_wc *file)
{
	t_wc	*tmp;
	int		count;
	char	**tab;
	int		i;

	tmp = file;
	count = bf_af_norme(tmp, bfwc, afwc);
	i = 0;
	tab = ft_malloc2(count, "char*");
	tmp = file;
	while (tmp)
	{
		if ((first_letter(tmp->file, bfwc) == true) \
		&& (last_letter(tmp->file, afwc) == true))
		{
			tab[i] = ft_strdup(tmp->file);
			i++;
		}
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	**wc_before(char *bfwc, t_wc *file)
{
	t_wc	*tmp;
	int		count;
	char	**tab;
	int		i;

	tmp = file;
	count = bf_norme(tmp, bfwc);
	i = 0;
	tab = ft_malloc2(count, "char*");
	tmp = file;
	while (tmp)
	{
		if ((first_letter(tmp->file, bfwc) == true))
		{
			tab[i] = ft_strdup(tmp->file);
			i++;
		}
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	**wc_after(char *afwc, t_wc *file)
{
	t_wc	*tmp;
	int		count;
	char	**tab;
	int		i;

	tmp = file;
	count = af_norme(tmp, afwc);
	i = 0;
	tab = ft_malloc2(count, "char*");
	tmp = file;
	while (tmp)
	{
		if ((last_letter(tmp->file, afwc) == true))
		{
			tab[i] = ft_strdup(tmp->file);
			i++;
		}
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	**wc_all(t_wc *file)
{
	t_wc	*tmp;
	int		count;
	char	**tab;
	int		i;

	count = 0;
	tmp = file;
	i = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	tab = ft_malloc2(count, "char*");
	tmp = file;
	while (tmp)
	{
		tab[i] = ft_strdup(tmp->file);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	ft_free_wc(t_wc *liste)
{
	t_wc	*tmp;

	tmp = liste;
	while (liste)
	{
		tmp = liste->next;
		free(liste->file);
		free(liste);
		liste = tmp;
	}
}
