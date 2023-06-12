#include "../../include/minishell.h"
static char *path_recuperation(t_env *env);
static char *join_path(char *str, char *path);

void create_cmd(t_binary *tree, t_env *env)
{
    int i = 0;
	tree->cmd = malloc(sizeof(t_cmd));
	tree->cmd->exec = false;
	tree->cmd->str = tree->data;
	tree->cmd->split_cmd = mini_split(tree->data);
    while(tree->cmd->split_cmd[i])
    {
        ft_printf("tab[%i] = %s\n", i, tree->cmd->split_cmd[i]);
        i++;
    }
    tree->cmd->path_cmd = cmd_recuperation(tree->cmd->split_cmd[0], env);
    ft_printf("%s\n",tree->cmd->path_cmd);
    if (ft_strcmp(tree->cmd->path_cmd,tree->cmd->split_cmd[0]) == 0)
        tree->cmd->path_cmd = NULL;
    //tree->cmd->in = open("/dev/stdin",STDIN_FILENO);
    //tree->cmd->out = open("/dev/stdout",STDOUT_FILENO);
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