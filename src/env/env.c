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

t_env *add_env(t_env *env, char **envp)
{
    int i;
    t_env *tmp;
    // creer fonction d initialisation ?
    env->name = NULL;
    env->data = NULL;
     
    i = 0;
    if (envp && envp[i])
    {
        while (envp[i])
        {
            tmp = ft_new_element(ft_strdup(envp[i]));
            if (!tmp || !tmp->data)
            {
                //clear(&env)
            }
            ft_add_back_lst(&env, tmp);
            i++;
        } 
    }
    return (env);
}
