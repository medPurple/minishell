#include "../../include/minishell.h"
void exec_meta( t_binary *tree, t_env *env);
bool execute_cmd(t_binary *tree, t_env *env);

void exec_recu(t_binary *tree, t_env *env)
{
	if (tree->right)
	{
		exec_recu(tree->left, env);
		exec_recu(tree->right, env);
	}
	else
	{
		if (is_a_meta(tree->data[0]))
			exec_meta(tree, env);
		else
		{
            if (tree->prev->right->cmd && tree->prev->right->cmd->exec == true)
                return;
            else
            {
                create_cmd(tree, env);
                tree->cmd->fork = fork();
                if (tree->cmd->fork == 0)
                    tree->cmd->exec = execute_cmd(tree, env);
                else
                    return;
            }


		}
	}
	return;
}

void exec_meta( t_binary *tree, t_env *env)
{
    if (ft_strcmp(tree->data, "|") == 0)
        ft_printf("PIPE\n");
    else if (ft_strcmp(tree->data, "||")== 0)
        mini_or(tree, env);
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

bool execute_cmd(t_binary *tree, t_env *env)
{
    ft_printf("%s\n",tree->cmd->path_cmd);
    if (execve(tree->cmd->path_cmd, tree->cmd->split_cmd, (char *const *)env) == -1)
    {
        ft_printf(" Error : Command execution\n");
        return false;
    }
    return (true);
}