/*
gestion environnement :
renvoyer les variables minimum indiquee dans le doc shell (cf doc)
gestion de la creation d une nouvelle variable et l'ajouter a la suite
de l'environnement

=> get env le path
et creer liste chainee recuperant l env ?
avec un titre et un contenu. exemple imprimer $FOO ( if $FOO =>search name liste chainee)

*/
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
		tmp = new_env_var(ft_strdup(envp[i]));
		ft_add_back_lst(env, tmp);
		i++;
	}
    return ;
}
