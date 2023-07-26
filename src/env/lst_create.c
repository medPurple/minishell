/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:14:16 by ml                #+#    #+#             */
/*   Updated: 2023/07/26 16:06:07 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_new_element(char *data)
{
	t_env	*element;
	int		i;

	i = 0;
	element = malloc(sizeof(t_env));
	if (!element)
		return (NULL);
	element->name = NULL;
	while (data[i] != '=' && data[i])
		i++;
	element->name = ft_malloc(i, "char");
	element->name[i] = '\0';
	i--;
	while (i >= 0)
	{
		element->name[i] = data[i];
		i--;
	}
	element->data = data;
	element->next = NULL;
	element->prev = NULL;
	return (element);
}

t_env	*ft_last_lst(t_env *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_back_lst(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = (*lst);
		(*lst) = ft_last_lst(*lst);
		(*lst)->next = new;
		(*lst)->next->prev = (*lst);
		(*lst) = tmp;
	}
}
