#include "../../include/minishell.h"

void mini_export(t_env *env, char *str)
{
	t_env *new;
	t_env *tmp;
	char *nstr;
	int i;
	int j;

	i = 0;
	j = 0;
	nstr = ft_malloc((ft_strlen(str) - 8),"char");
	tmp = env;
	while(str[i] != ' ')
		i++;
	i++;
	while(str[i] != '\0' )
	{
		if (str[i] == '"')
			i++;
		else
		{
			nstr[j] = str[i];
			i++;
			j++;
		}
	}
	free(str);
	new = ft_new_element(nstr);
	ft_add_back_lst(&env, new);
	env = tmp;
}