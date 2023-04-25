#include "../../include/minishell.h"

void mini_export(t_env *env, char *str)
{
	t_env *new;
	t_env *tmp;

	tmp = env;
	new = ft_new_element(str);
	ft_add_back_lst(&env, new);
	env = tmp;
}