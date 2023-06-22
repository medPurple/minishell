/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:16:24 by wmessmer          #+#    #+#             */
/*   Updated: 2023/06/22 15:30:08 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static int count_arg(char **tab);
static char *find_dir(t_env *env);
static void changedir(char *destination, char *last, t_env *env);

void mini_cd(t_env *env, t_binary *tree)
{
	int i;
	char *str = NULL;
	char *path = NULL;
	str = getcwd(NULL,0);
	if (count_arg(tree->cmd->split_cmd) > 2)
		ft_printf("cd: too many arguments\n");
	else
	{
		if (count_arg(tree->cmd->split_cmd) == 1)
				changedir(find_dir(env),str,env);
		else
		{
			
			i = ft_strlen(str);
			if (ft_strcmp(tree->cmd->split_cmd[1],"..")== 0)
			{
				while(str[i] != '/')
					i--;
				if (i == 0)
					path = "/";
				else
					path = ft_limited_strdup(str,0,i - 1);
				if (opendir((const char*)path) != NULL)
					changedir(path,str,env);
				else
					ft_printf("Wrong cd");	
			}
			else	
			{
				path = ft_strjoin(str,"/");
				path = ft_strjoin(path,tree->cmd->split_cmd[1]);
				if (opendir((const char*)path) != NULL)
					changedir(path,str,env);
				else
					ft_printf("Wrong cd");		
			}
		}
	}
}

static int count_arg(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		i++;
	return (i);
}

static char *find_dir(t_env *env)
{
	const char *str;
	t_env *tmp;

	str = NULL;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name,"HOME") == 0)
			return(ft_limited_strdup(tmp->data,5, ft_strlen(tmp->data)));	
		tmp = tmp->next;		
	}
	return (NULL);
}

static void changedir(char *destination, char *last, t_env *env)
{
	t_env *tmp = env;

	ft_printf("[D] %s\n",destination);
	ft_printf("[L] %s\n",last);

	chdir(destination);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
		{
			tmp->data = ft_strjoin("OLDPWD=",last);
		}
		tmp = tmp->next;
	}
	free(destination);
}