#include "../../include/minishell.h"

void exec_meta( t_binary *tree, t_minishell *mini);
void execute_cmd(t_binary *tree, t_minishell *mini);
void exec_buildin(t_binary *tree, t_minishell *mini);
void    exec_send(t_binary *tree, t_minishell *mini);

void exec_recu(t_minishell *mini, t_binary *tree)
{
    int i;

    i = 0;
   if (tree->parentheses == true)
       expand_parentheses_and_execute(tree, mini);
   else if (tree->right)
	{
        exec_recu(mini, tree->left);
	    exec_recu(mini, tree->right);
	}
	else
	{
		if (is_a_meta(tree->data, 0))
			exec_meta(tree, mini);
		else
		{
            if (tree->cmd->exec == 1 || tree->cmd->exec == -1)
                return;
            else
            {
                tree->cmd->check_pipe = -1;
                while(tree->cmd->split_cmd[i])
                {
                    if (is_a_pipe(tree->cmd->split_cmd[i]) == true)
                    {
                        tree->cmd->check_pipe = 1;
                        pipex(tree, mini);
                        break;
                    }
                    i++;
                }
                if (tree->cmd->check_pipe == -1)
                {
                    i = cmd_redir_malloc(tree, 0);
                    if (i < 0)
                    {
                        ft_printf("error_gestion\n");
                        return;
                    }
                    execution_choice(tree, mini);
                }
            }
        }
    }
	return;
}

void    exec_send(t_binary *tree, t_minishell *mini)
{
    int status;
	tree->cmd->exec = 1;
    if (is_here_doc(tree) >= 1)
	{
		tree->cmd->check_here_doc = 1;
		mini_here_doc(tree->redir->redir_file, tree);
    }
    tree->cmd->fork = fork();
    if (tree->cmd->fork == -1)
        perror("fork");
	else if(tree->cmd->fork == 0)
    {
        exec_cmd_redir(tree);
        if (is_a_buildin(tree->cmd->exec_cmd[0]) == 0)
		    execute_cmd(tree, mini);
        else
            exec_buildin_child(tree, mini);
    }
    else
    {
        while(wait(&status) != -1)
                ;
        if (WEXITSTATUS(status) > 0)
            tree->cmd->exec = -1;
    }
    return ;
}

void exec_meta( t_binary *tree, t_minishell *mini)
{
    if (ft_strcmp(tree->data, "||")== 0)
        mini_or(tree, mini);
    else if (ft_strcmp(tree->data, "&&")== 0)
        mini_and(tree, mini);
    else
        ft_printf("error meta\n");
}

void execute_cmd(t_binary *tree, t_minishell *mini)
{
    if (tree->cmd->path_cmd)
		free(tree->cmd->path_cmd);
    tree->cmd->path_cmd =  cmd_recuperation(tree->cmd->exec_cmd[0], mini->env);
    if (tree->cmd->path_cmd != NULL)
    {
        if (execve(tree->cmd->path_cmd, tree->cmd->exec_cmd, mini->envp) == -1)
        {
            ft_free_tab(tree->cmd->exec_cmd);
            ft_perror(" Error : Command execution\n");
        }
    }
    else if (ft_strchr(tree->cmd->exec_cmd[0], '/') != NULL)
    {
        tree->cmd->path_cmd = tree->cmd->exec_cmd[0];
        if (execve(tree->cmd->path_cmd, tree->cmd->exec_cmd, mini->envp) == -1)
        {
            ft_free_tab(tree->cmd->exec_cmd);
            ft_perror(" Error : Command execution\n");
        }
    }
    else
    {
        ft_free_tab(tree->cmd->exec_cmd);
		ft_perror("path");
    }
    //ft_free_tab(tree->cmd->exec_cmd);
}

void exec_buildin(t_binary *tree, t_minishell *mini)
{
    tree->cmd->exec = 1;
    if (ft_strcmp(tree->cmd->exec_cmd[0], "cd") == 0)
        mini_cd(mini->env, tree);
    else if (ft_strcmp(tree->cmd->exec_cmd[0], "export") == 0)
        mini_export(&mini->env,tree->cmd->exec_cmd);
    else if (ft_strcmp(tree->cmd->exec_cmd[0], "unset") == 0)
        mini_unset(&mini->env,tree->cmd->exec_cmd);
    else if (ft_strcmp(tree->cmd->exec_cmd[0], "exit") == 0)
        mini_exit(mini);
}
void exec_buildin_child(t_binary *tree, t_minishell *mini)
{
    if (ft_strcmp(tree->cmd->exec_cmd[0], "echo") == 0)
        mini_echo(tree);
    else if (ft_strcmp(tree->cmd->exec_cmd[0], "pwd") == 0)
         mini_pwd(mini->env);
   else if (ft_strcmp(tree->cmd->exec_cmd[0], "env") == 0)
        mini_env(mini->env);
    exit(EXIT_SUCCESS);
}
