#include "../../include/minishell.h"

void create_cmd(t_binary *tree)
{
	tree->cmd = malloc(sizeof(t_cmd));
	tree->cmd->exec = false;
	tree->cmd->str = tree->data;
	tree->cmd->split_cmd = mini_split(tree->data);
}
