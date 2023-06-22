#include "../../include/minishell.h"

void mini_pwd(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name,"PWD") == 0)
			ft_printf("%s\n",tmp->data+4);
		tmp = tmp->next;
	}
}
