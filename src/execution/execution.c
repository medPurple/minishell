#include "../../include/minishell.h"
void exec_meta( t_binary *tree, t_minishell *mini);
void execute_cmd(t_binary *tree, char **envp);

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
                tree->cmd->fork = fork();
                if (tree->cmd->fork == -1)
                    perror("fork");
                if (tree->cmd->fork == 0)
                    execute_cmd(tree, mini->envp);
                   // return;
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

void execute_cmd(t_binary *tree, char **envp)
{
    tree->cmd->exec = true;
    if (tree->cmd->path_cmd)
    {
        if (execve(tree->cmd->path_cmd, tree->cmd->split_cmd, envp) == -1)
        {
            ft_free_tab(tree->cmd->split_cmd);
            ft_perror(" Error : Command execution\n");
        }
    }
    else if (ft_strchr(tree->cmd->split_cmd[0], '/') != NULL)
    {
        tree->cmd->path_cmd = tree->cmd->split_cmd[0];
        if (execve(tree->cmd->path_cmd, tree->cmd->split_cmd, envp) == -1)
        {
            ft_free_tab(tree->cmd->split_cmd);
            ft_perror(" Error : Command execution\n");
        }
    }
    else
    {
        ft_free_tab(tree->cmd->split_cmd);
		ft_perror("path");
    }
    ft_free_tab(tree->cmd->split_cmd);
}
