/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:14:16 by ml                #+#    #+#             */
/*   Updated: 2023/04/21 15:14:41 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_new_element(char *data)
{
	t_env	*element;

	element = malloc(sizeof(t_env));
	if (!element)
		return (NULL);
	element->data = data;
	element->next = NULL;
	return (element);
}

t_env	*ft_last_lst(t_env *lst)
{
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_add_back_lst(t_env **lst, t_env *new)
{
	t_env	*str;
	t_env   *tmp;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = (*lst);
		str = ft_last_lst(*lst);
		str->next = new;
		(*lst) = tmp;
	}
	//(*lst) = tmp;
}