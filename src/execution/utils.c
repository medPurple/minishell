#include "../../include/minishell.h"
static char *path_recuperation(t_env *env);
static char *join_path(char *str, char *path);

void create_cmd(t_binary *tree)
{
	tree->cmd = malloc(sizeof(t_cmd));
	tree->cmd->exec = 0;
	tree->cmd->str = tree->data;
	tree->cmd->split_cmd = mini_split(tree->data);
  tree->cmd->path_cmd = NULL;
  tree->cmd->exec_cmd = NULL;
}

char *cmd_recuperation(char *str, t_env *env)
{
    char **path;
    int i;
    char *cmd;

    i = 0;
    path = ft_split(path_recuperation(env), ':');
    while (path[i])
    {
        cmd = join_path(str,path[i]);
        if (access(cmd, 0) == 0)
            return (cmd);
        free(cmd);
        i++;
    }
    return(str);
}

static char *path_recuperation(t_env *env)
{
    t_env *tmp;

    tmp = env;
    while(tmp)
    {
        if (ft_strcmp(tmp->name, "PATH")==0)
            return(tmp->data + 5);
        tmp = tmp->next;
    }
    return (NULL);
}

static char *join_path(char *str, char *path)
{
    path = ft_strjoin(path,"/");
    str = ft_strjoin(path,str);
    return (str);
}

void	ft_free_lst(t_redirection *stack)
{
	t_redirection	*tmp;

	if (!stack)
		return ;
	while (stack)
	{
		tmp = (stack)->next;
		free(stack);
		(stack) = tmp;
	}
    free(stack);
}
