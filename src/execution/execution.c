#include "../../include/minishell.h"

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
			ft_printf("META\n");
		else
		{
			create_cmd(tree);
			ft_printf("CMD\n");
		}
	}
	return;
}
