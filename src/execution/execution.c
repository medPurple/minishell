#include "../../include/minishell.h"

void execution(t_binary *tree, t_env *env)
{
	if (tree->right)
	{
		execution(tree->left, env);
	}
}