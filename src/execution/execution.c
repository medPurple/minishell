#include "../../include/minishell.h"
void exec_meta( t_binary *tree, t_minishell *mini);
bool execute_cmd(t_binary *tree, char **envp);

void exec_recu(t_minishell *mini, t_binary *tree)
{
	if (tree->right)
	{
		exec_recu(mini, tree->left);
		exec_recu(mini, tree->right);
	}
	else
	{
		if (is_a_meta(tree->data[0]))
			exec_meta(tree, mini);
		else
		{
           // if (tree->prev->right->left->cmd && tree->prev->right->cmd->exec == true)
            //    return;
            //else
            //{
                create_cmd(tree, mini->env);
                tree->cmd->fork = fork();
                if (tree->cmd->fork == 0)
                    tree->cmd->exec = execute_cmd(tree, mini->envp);
                else
                    return;
            //}
		}
	}
	return;
}

void exec_meta( t_binary *tree, t_minishell *mini)
{
    if (ft_strcmp(tree->data, "|") == 0)
        ft_printf("PIPE\n");
    else if (ft_strcmp(tree->data, "||")== 0)
        mini_or(tree, mini);
    else if (ft_strcmp(tree->data, "&&")== 0)
        ft_printf("AND\n");
    else if (ft_strcmp(tree->data, "<")== 0)
        ft_printf("REDIR\n");
    else if (ft_strcmp(tree->data, ">")== 0)
        ft_printf("REDIR\n");
    else if (ft_strcmp(tree->data, ">>")== 0)
        ft_printf("IDK\n");
    else if (ft_strcmp(tree->data, "<<")== 0)
        ft_printf("HERE\n");
    else
        ft_printf("error meta\n");
}

bool execute_cmd(t_binary *tree, char **envp)
{
    if (execve(tree->cmd->path_cmd, tree->cmd->split_cmd, envp) == -1)
    {
        perror(" Error : Command execution\n");
        return false;
    }
    return (true);
}