#include "include/minishell.h"
static void recu_print(t_binary *tree, int i);
static void print_data(t_binary *tree, int i);

void print_binary(t_binary *tree) {

	int i = 3;
	tree->visualiser = 1;
	recu_print(tree, i);
	while (wait(NULL) > 0)
		;
}

static void recu_print(t_binary *tree, int i) {
	pid_t left;
	pid_t right;
	print_data(tree, i);
	while (wait(NULL) > 0)
		;
	if (tree->left != NULL)
	{
		left = fork();
		tree->left->visualiser = -1;
		if (left == 0)
		{
			recu_print(tree->left, i + 1);
			while (wait(NULL) > 0)
				;
			exit(0);
		}
	}
	if (tree->right != NULL)
	{
		right = fork();
		if (tree->visualiser == 1 && (tree->prev == NULL || tree->prev->visualiser == 1))
			tree->right->visualiser = 1;
		else
			tree->right->visualiser = 0;
		if (right == 0)
		{
			recu_print(tree->right,i + 2);
			while (wait(NULL) > 0)
				;
			exit(0);
		}
	}
}

static void print_data(t_binary *tree, int i) {
	int j = 0;
	if (tree->visualiser == -1){
		while (j < i)
		{
			ft_printf("\t");
			j++;
		}
	} else
		ft_printf("\t");
	while (wait(NULL) > 0)
		;
	if (tree->visualiser == 1)
		ft_printf("| %s |\n\n", tree->data);
	else
		ft_printf("| %s |", tree->data);
	while (wait(NULL) > 0)
		;
}