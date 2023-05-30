#include "../../include/minishell.h"
static char *replace_doll(char *str, t_env *env, int position);
static char *search_in_env(char *var, t_env *env, char *str);
static char *join_all_part(char *str, char *add);


void expand(t_binary *tree, t_env *env)
{
	int i;

	i = 0;
	//expand_quotes(tree, env);
	//verfie premier aractere et ledeclare executable ou non
	while (tree->data[i])
	{
		if (tree->data[i] == '$')
		{
			tree->data = replace_doll(tree->data, env, i+1);
			ft_printf(" passage %i = %s\n", i, tree->data);
		}
		else if (tree->data[i] == '\'')
			i = pass_quotes(tree->data, i) + 1;
		else
			i++;

	}
}

static char *replace_doll(char *str, t_env *env, int position)
{
	int i;
	char *var;

	i = position;
	while(str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		i++;
	i = i - position;

	var = ft_malloc(i, "char");
	i = 0;
	while(str[position]  != ' ' && str[position] != '\t' && str[position] != '\0'
		&& str[position] != '\"')
	{
		var[i] = str[position];
		i++;
		position++;
	}
	var[i] = '\0';
	str = search_in_env(var,env, str);
	return(str);
}

static char *search_in_env(char *var, t_env *env, char *str)
{
	t_env *tmp;
	int i;
	int j;
	char *add;

	i = 0;
	j = 0;
	add = NULL;
	tmp = env;
	while(env != NULL) {
		if (ft_strncmp(env->data, var, ft_strlen(var)) == 0)
			break;
		env = env->next;
	}
	if (env != NULL)
	{
		while(env->data[i] != '=')
			i++;
		i++;
		add = ft_malloc((ft_strlen(env->data) - i), "char");

		while(env->data[i] != '\0')
			add[j++] = env->data[i++];
		add[j] = '\0';
		str = join_all_part(str, add);
	}
	env = tmp;
	return (str);
}

static char *join_all_part(char *str, char *add)
{
	int i;
	int j;
	char *before;
	char *after;

	i = 0;
	j = 0;
	while (str[i] != '$')
		i++;
	before = ft_malloc(i+1,"char");
	while (j < i - 1)
	{
		before[j] = str[j];
		j++;
	}
	before[j] = ' ';
	before[j + 1] = '\0';
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	while (str[i] == ' ' && str[i] != '\0' && str[i] != '\t')
		i++;
	j = 0;
	after = ft_malloc((ft_strlen(str) - i), "char");
	while (str[i] != '\0')
		after[j++] = str[i++];
	after[j] = '\0';
	free(str);
	str = ft_strjoin(before, add);
	str = ft_strjoin(str, after);
	return (str);
}
