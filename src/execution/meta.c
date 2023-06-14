#include "../../include/minishell.h"

void mini_or(t_binary *tree, t_minishell *mini)
{
    if (tree->prev->prev->left->cmd->exec == 1)
    {
        if (tree->prev->right->right)
            tree->prev->right->left->cmd->exec = 1;
        else
            tree->prev->right->cmd->exec = 1;
        return;
    }
    else
        exec_recu(mini, tree->prev->right);

}

void mini_and(t_binary *tree, t_minishell *mini)
{
    if (tree->prev->prev->left->cmd->exec == -1)
    {
        if (tree->prev->right->right)
            tree->prev->right->left->cmd->exec = -1;
        else
            tree->prev->right->cmd->exec = -1;
        return ;
    }
    else
        exec_recu(mini, tree->prev->right);
}
