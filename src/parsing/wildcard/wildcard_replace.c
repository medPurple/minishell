#include "../../../include/minishell.h"

char **wc_before_and_after(char *bfwc, char *afwc, t_wc *file)
{
	t_wc *tmp;
	int count;
	char **tab;
	int i;

	count = 0;
	tmp = file;
	i = 0;
	while(tmp)
	{
		if ((first_letter(tmp->file,bfwc) == true) && (last_letter(tmp->file,afwc) == true))
			count++;
		tmp = tmp->next;
	}
	tab = ft_malloc2(count, "char*");
	tmp = file;
	while(tmp)
	{
		if ((first_letter(tmp->file,bfwc) == true) && (last_letter(tmp->file,afwc) == true))
		{
			tab[i] = tmp->file;
			i++;
		}
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return(tab);
}

char **wc_before(char *bfwc, t_wc *file)
{
	t_wc *tmp;
	int count;
	char **tab;
	int i;

	count = 0;
	tmp = file;
	i = 0;
	while(tmp)
	{
		if ((first_letter(tmp->file,bfwc) == true))
			count++;
		tmp = tmp->next;
	}
	tab = ft_malloc2(count, "char*");
	tmp = file;
	while(tmp)
	{
		if ((first_letter(tmp->file,bfwc) == true))
		{
			tab[i] = tmp->file;
			i++;
		}
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return(tab);
}

char **wc_after(char *afwc, t_wc *file)
{
	t_wc *tmp;
	int count;
	char **tab;
	int i;

	count = 0;
	tmp = file;
	i = 0;
	while(tmp)
	{
		if ((last_letter(tmp->file,afwc) == true))
			count++;
		tmp = tmp->next;
	}
	tab = ft_malloc2(count, "char*");
	tmp = file;
	while(tmp)
	{
		if ((last_letter(tmp->file,afwc) == true))
		{
			tab[i] = tmp->file;
			i++;
		}
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return(tab);
}

char **wc_all(t_wc *file)
{
	t_wc *tmp;
	int count;
	char **tab;
	int i;

	count = 0;
	tmp = file;
	i = 0;
	while(tmp)
	{
		count++;
		tmp = tmp->next;
	}
	tab = ft_malloc2(count, "char*");
	tmp = file;
	while(tmp)
	{
		tab[i] = tmp->file;
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return(tab);
}