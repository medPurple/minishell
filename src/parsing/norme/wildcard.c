/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:55:13 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/12 16:59:33 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	bf_af_norme(t_wc *tmp, char *bfwc, char *afwc)
{
	int	count;

	count = 0;
	while (tmp)
	{
		if ((first_letter(tmp->file, bfwc) == true) \
		&& (last_letter(tmp->file, afwc) == true))
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	bf_norme(t_wc *tmp, char *bfwc)
{
	int	count;

	count = 0;
	while (tmp)
	{
		if ((first_letter(tmp->file, bfwc) == true))
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	af_norme(t_wc *tmp, char *afwc)
{
	int	count;

	count = 0;
	while (tmp)
	{
		if ((last_letter(tmp->file, afwc) == true))
			count++;
		tmp = tmp->next;
	}
	return (count);
}
