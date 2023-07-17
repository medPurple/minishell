/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_create_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:28 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/17 15:28:26 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_redirection	*ft_new_redirection(char *redir, char *file, int j)
{
	t_redirection	*element;
	int	i;

	i = 1;
	element = malloc(sizeof(t_redirection));
	if (!element)
		return (NULL);
	element->redir_cmd = NULL;
	element->redir_file = NULL;
	if (redir[0] == '|')
	{
		element->redir_cmd = ft_malloc(ft_strlen(redir) - 1, "char");
		while (redir[i] != '\0')
			element->redir_cmd[j++] = redir[i++];
		element->redir_cmd[j] = '\0';
	}
	else
		element->redir_cmd = redir;
	element->redir_file = file;
	element->next = NULL;
	return (element);
}

t_redirection	*ft_last_lst_redirection(t_redirection *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_add_back_lst_redirection(t_redirection **lst, t_redirection *new)
{
	t_redirection	*str;

	if (!(*lst))
	{
		*lst = new;
	}
	else
	{
		str = ft_last_lst_redirection(*lst);
		str->next = new;
	}
}
