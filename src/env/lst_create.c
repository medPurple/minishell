/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:14:16 by ml                #+#    #+#             */
/*   Updated: 2023/05/05 09:29:54 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_new_element(char *data)
{
	t_env	*element;
	int i;

	i = 0;
	element = malloc(sizeof(t_env));
	if (!element)
		return (NULL);
	while(data[i] != '=')
		i++;
	element->name = malloc(sizeof (char *) * i + 1);
	i--;
	while (i >= 0)
	{
		element->name[i] = data[i];
		i--;
	}
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
}
