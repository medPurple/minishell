#include "../../include/minishell.h"
static bool is_valid_bf(char *str);
static bool has_equals(char *str);

void mini_export(t_env **env, char **tab)
{
	t_env *tmp;
	int i;

	i = 1;
	while (tab[i])
	{
		if (is_valid_bf(tab[i]) == true && has_equals(tab[i]) == true)
		{
			tmp = ft_new_element(tab[i]);
			ft_add_back_lst(env, tmp);
		}
		else if (is_valid_bf(tab[i]) == true && has_equals(tab[i]) == false)
			ft_printf("\n");
		else
			ft_printf("minishell: export: %s : not a valid identifier\n", tab[i]);
		i++;
	}
	//ft_free_tab(tab);
}

static bool is_valid_bf(char *str)
{
	int i;
	int j;
	char *lim;

	i = 0;
	j = 0;
	while (str[i] != '=' && str[i])
		i++;
	lim = ft_limited_strdup(str,0,i-1);
	while (lim[j])
	{
		if (!((lim[j] >= 'a' && lim[j] <= 'z') || (lim[j] >= 'A' && lim[j] <= 'Z') ||
			(lim[j] >= '0' && lim[j] <= '9') ))
			return false;
		j++;
	}
	return true;

}

static bool has_equals(char *str)
{
	int i;

	i = 0;

	while(str[i])
	{
		if( str[i] == '=')
			return true;
		i++;
	}
	return false;
}

/*export skkf sdfsdf=sdfsdf "readasd"="dfsdf" resrwe="fsdf" "fsdf"=fsfs*/