#include "../../include/minishell.h"

void mini_or(t_binary *tree, t_minishell *mini)
{
    if (tree->prev->prev->left->cmd->exec == true)
    {
        tree->prev->right->left->cmd->exec = true;
        return;
    }
    else
        exec_recu(mini, tree->prev->right);

}