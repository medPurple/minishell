#include "../../include/minishell.h"

void mini_or(t_binary *tree, t_env *env)
{
    if (tree->prev->prev->left->cmd->exec == true)
    {
        tree->prev->right->cmd->exec = true;
        return;
    }
    else
        exec_recu(tree->prev->right, env);

}