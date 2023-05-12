
/*
si mauvaise commande == foo => afficher message d erreur et renvoyer un prompt
si bonne commande == gestion des flags dans les commandes : ls -l -a- F ou ls -laF doivent etre interpretes de la meme facon par exemple // cad donner le mm resultat // puis executer et renvoyer un prompt
					== gestion des built in ? si built in -> aller chercher ces fonctiosn et faire la meme.
		gestion du tild (~) ?


		quote envoie a la commande juste le contenue entre les quotes
		doubles quotes envoie le contenue a la commande et essai d'interpreter si il trouve des commandes dedans
		simple quote = n essaye pas d interpreter ce qui se situe entre ' '
		double quotes = essaye d interpreter ce qui se situe entre "  " si ecrit de cette facon : $(cmd Arg) -> ex : $(cat Makefile)
		->pose la qst de l interpretation du $ ? = cad verifier ce qu il y a apres .

		A GERER  : | & < > $ " '  <space>  <tab>  <newline> *

seules les commandes builtin ne doivent pas etre interpretees en tant que commande
        if (is_a_quotes(str) == 1)
            return(-1);
 */
#include "../../include/minishell.h"

static void tree_creation(t_binary *tree, t_env *env);
//static int search_command(char *str, t_env *env);
static t_binary *new_branche(t_binary *tree, char *str);
static void new_data(t_binary *tree, t_env *env);

void mini_parse(t_minishell *mini, char *str)
{
    mini->tree = new_branche(mini->tree, str);
    while (mini->tree->end != 1)
    {
        ft_printf("=====================================================\n");
        tree_creation(mini->tree, mini->env);
        ft_printf("tree-> data : %s\n", mini->tree->data);
        //ces printf ci-dessous font segfault si pas de cmd dans readline
        //ft_printf("left -> %s\n", mini->tree->left->data);
        //ft_printf("right -> %s\n", mini->tree->right->data);
    }
}

static void tree_creation(t_binary *tree, t_env *env)
{
    if (tree->left == NULL)
        new_data(tree, env);
   // ft_printf("command -> %s\n", tree->command);
   // ft_printf("rest -> %s\n\n\n", tree->rest);
    if (tree->command == NULL)
    {
        tree->end = 1;
        return ;
    }
    tree->left = new_branche(tree->left, tree->command);
    tree->right = new_branche(tree->right, tree->rest);
    ft_printf ("\n\ntree left = %s |||| ", tree->left->data);
    ft_printf ("tree right = %s \n", tree->right->data);
    tree->right->prev = tree;
    tree->left->prev = tree;

	if (tree->right != NULL && tree->right->end != 1)
		tree_creation(tree->right, env);
    if (tree->right->end == 1)
        tree->end = 1;
   // if (tree->prev != NULL)
     //   ft_printf("prev->data : %s |||| data->actual : %s\n", tree->prev->data, tree->data);
    //ft_printf("end -> %d\n", tree->end);

    return;
}

static t_binary *new_branche(t_binary *tree, char *str)
{
    tree = malloc(sizeof(t_binary));
    tree->data = NULL;
    tree->data = malloc(sizeof(char) * (ft_strlen(str) + 1));
    tree->data = str;
    tree->end = 0;
    tree->prev = NULL;
    tree->left = NULL;
    tree->right = NULL;
    tree->command = NULL;
    tree->rest = NULL;
    return (tree);
}

static void new_data(t_binary *tree, t_env *env)
{
    int size_data;
    int i;
    int j;

    i = 0;
    j = 0;
   ft_printf( "tree data before search : %s\n", tree->data);//else if (tree->data[i] == '$' || tree->data[i] == '*')
    size_data = search_data(tree->data, env);
    ft_printf("size_data : %i\n", size_data);
    if (size_data == -1)
    {
        tree->end = 1;
        return;
    }
    tree->command = malloc(sizeof(char) * size_data + 1);
    while (i <= size_data)
    {
        tree->command[i] = tree->data[i];
        i++;
    }
    tree->command[i] = '\0';
    tree->rest = malloc(sizeof(char ) * (ft_strlen(tree->data) - size_data) + 1);
    while (tree->data[i])
    {
        tree->rest[j] = tree->data[i];
        i++;
        j++;
    }
    tree->rest[j] = '\0';
}
