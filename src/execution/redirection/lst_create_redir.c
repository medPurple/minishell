#include "../../../include/minishell.h"

t_redirection	*ft_new_redirection(char *redir, char *file)
{
	t_redirection	*element;
	
	element = malloc(sizeof(t_redirection));
	if (!element)
		return (NULL);
	element->redir_cmd = NULL;
	element->redir_file = NULL;
	element->redir_cmd = redir;
	if (redir[0] != '|')
		element->redir_file = file;
	element->next = NULL;
	return (element);
}

t_redirection	*ft_last_lst_redirection(t_redirection *lst)
{

	if (!lst)
		return(NULL);
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
