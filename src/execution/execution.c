#include "../../include/minishell.h"
void exec_meta( t_binary *tree, t_minishell *mini);
void execute_cmd(t_binary *tree, char **envp);
void exec_buildin(t_binary *tree, t_minishell *mini);

void exec_recu(t_minishell *mini, t_binary *tree)
{
	int i;

    i = 0;
    if (tree->right)
	{
		exec_recu(mini, tree->left);
		exec_recu(mini, tree->right);
	}
	else
	{
		if (is_a_meta(tree->data, 0)) // ne prend en compte que && et ||
			exec_meta(tree, mini);
		else
		{
            if (tree->cmd->exec == 1 || tree->cmd->exec == -1) // toujours utile pour les && et ||
                return;
            else
            {
                // je parcours la chaine de caractere et si je croise un pipe je split
                while(tree->cmd->split_cmd[i])
                {
                    if (tree->cmd->split_cmd[i] != NULL && is_a_pipe(tree->cmd->split_cmd[i]) == true)
                    {
                         // changement des redirections avant exec commande
                        i++;
                    }
                    if (tree->cmd->exec_cmd)
                        ft_free_tab(tree->cmd->exec_cmd);
                    i = malloc_cmd_redir(mini, tree, i); // jai malloc 1 cmd en comprenant les possibles redirections | je veux malloc tant qu il reste des cmd a malloc
                    tree->cmd->exec = 1;
                    execution_choice(tree, mini, i);
                    //i++;
                }
            }
        }
    }

	return;
}

void    exec_send(t_binary *tree, t_minishell *mini)
{
    char	buf[6];
	int	ret;
    t_redirection	*tmp;

    tmp = tree->redir;
	tree->cmd->exec = 1;
    if (pipe(tree->cmd->fd) == -1)
        perror("pipe");
    tree->cmd->fork = fork();
    if (tree->cmd->fork == -1)
        perror("fork");
	else if(tree->cmd->fork == 0)
    {
		exec_cmd_redir(tree, mini);
        if (is_a_buildin(tree->cmd->exec_cmd[0]) != 1)
		    execute_cmd(tree, mini->envp);
        if (is_a_buildin(tree->cmd->exec_cmd[0]) == 1)
            exec_buildin_child(tree, mini);
    }
    else
    {
        close(tree->cmd->fd[1]);
        ret = read(tree->cmd->fd[0], buf, 10);
        buf[ret] = '\0';
        close(tree->cmd->fd[0]);
        if (ft_strcmp(buf, "false") == 0)
            tree->cmd->exec = -1;
        while(wait(NULL) != -1)
                ;
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

void execute_cmd(t_binary *tree, char **envp)
{
    ft_printf("exec in = %d\n",tree->cmd->exec);
    if (tree->cmd->path_cmd)
    {
        if (execve(tree->cmd->path_cmd, tree->cmd->exec_cmd, envp) == -1)
        {
            close(tree->cmd->fd[0]);
            write(tree->cmd->fd[1], "false", 5);
            close(tree->cmd->fd[1]);
            ft_free_tab(tree->cmd->exec_cmd);
            ft_perror(" Error : Command execution\n");
        }
    }
    else if (ft_strchr(tree->cmd->exec_cmd[0], '/') != NULL)
    {
        tree->cmd->path_cmd = tree->cmd->exec_cmd[0];
        if (execve(tree->cmd->path_cmd, tree->cmd->exec_cmd, envp) == -1)
        {
            close(tree->cmd->fd[0]);
            write(tree->cmd->fd[1], "false", 5);
            ft_free_tab(tree->cmd->exec_cmd);
            ft_perror(" Error : Command execution\n");
        }
    }
    else
    {
        close(tree->cmd->fd[0]);
        write(tree->cmd->fd[1], "false", 5);
        close(tree->cmd->fd[1]);
        ft_free_tab(tree->cmd->exec_cmd);
		ft_perror("path");
    }
    ft_free_tab(tree->cmd->exec_cmd);
}

void exec_buildin(t_binary *tree, t_minishell *mini)
{
    if (ft_strcmp(tree->cmd->exec_cmd[0], "cd") == 0)
        mini_cd(mini->env, tree);
    else if (ft_strcmp(tree->cmd->exec_cmd[0], "exit") == 0)
        exit(0);
}
void exec_buildin_child(t_binary *tree, t_minishell *mini)
{
    if (ft_strcmp(tree->cmd->exec_cmd[0], "echo") == 0)
        mini_echo(tree);
    else if (ft_strcmp(tree->cmd->exec_cmd[0], "pwd") == 0)
         mini_pwd(mini->env);
    exit(EXIT_SUCCESS);
}
