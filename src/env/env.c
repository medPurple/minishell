#include "../../include/minishell.h"

void add_env(t_env **env, char **envp)
{
    int i;
    t_env *tmp;
     
    i = 0;
	if (!envp)
		return ;
    while (envp[i])
    {
		tmp = ft_new_element(ft_strdup(envp[i]));
		ft_add_back_lst(env, tmp);
		i++;
	}
    return ;
}
