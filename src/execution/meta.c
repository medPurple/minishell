#include "../../include/minishell.h"

void mini_or(t_binary *tree, t_minishell *mini)
{
    if (tree->prev->prev->left->cmd->exec == true)
    {
        if (tree->prev->right->right)
            tree->prev->right->left->cmd->exec = true;
        else
            tree->prev->right->cmd->exec = true;
        return;
    }
    else
        exec_recu(mini, tree->prev->right);

}

void mini_and(t_binary *tree, t_minishell *mini)
{
    if (tree->prev->prev->left->cmd->exec == true)
        exec_recu(mini, tree->prev->right);
    else
    {
        tree->prev->right->left->cmd->exec = false;// on arrete d executer
        return ;
    }
}
