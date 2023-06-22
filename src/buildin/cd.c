#include "../../include/minishell.h"

int count_arg(char **tab);
char *find_dir(char *destination, t_env *env);

void mini_cd(t_env *env, t_binary *tree)
{
	int i;
	char *str;
	char *path = NULL;
	ft_printf("ARG : %d\n",count_arg(tree->cmd->exec_cmd));
	if (count_arg(tree->cmd->exec_cmd) > 2)
		ft_printf("cd: too many arguments\n");
	else
	{
		if (count_arg(tree->cmd->exec_cmd) == 1)
			chdir(find_dir("HOME", env));
		else
		{

			str = getcwd(NULL,0);
			i = ft_strlen(str);
			if (ft_strcmp(tree->cmd->exec_cmd[1],"..")== 0)
			{
				while(str[i] != '/')
					i--;
				if (i == 0)
					path = "/";
				else
					path = ft_limited_strdup(str,0,i - 1);
				if (opendir((const char*)path) != NULL)
					chdir(path);
				else
					ft_printf("Wrong cd");
			}
			else
			{
				path = ft_strjoin(str,"/");
				path = ft_strjoin(path,tree->cmd->exec_cmd[1]);
				if (opendir((const char*)path) != NULL)
					chdir(path);
				else
					ft_printf("Wrong cd");
			}
		}
	}
}

int count_arg(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		i++;
	return (i);
}

char *find_dir(char *destination, t_env *env)
{
	const char *str;
	t_env *tmp;
	char *old;

	str = NULL;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name,"PWD") == 0)
				old = ft_strdup(tmp->data + 4);
		tmp = tmp->next;
	}
	tmp = env;
	while(tmp)
	{
		if(ft_strcmp(tmp->name,destination) == 0)
			str = ft_strdup(tmp->data + 5);
		tmp = tmp->next;
	}
	tmp = env;
	while (tmp)
	{

		if (ft_strcmp(tmp->name,"PWD") == 0)
		{
			tmp->data = ft_strjoin("PWD=",(char*)str);
			break;
		}
		tmp = tmp->next;
	}
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name,"OLDPWD") == 0)
				tmp->data = ft_strjoin("OLDPWD=", old);
		tmp = tmp->next;
	}
	return ((char*)str);
}
