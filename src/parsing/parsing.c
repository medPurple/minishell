
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


 */
#include "../../include/minishell.h"

static void nom_de_fonction(t_binary *tree, t_env *env);
static int search_command(char *str, t_env *env);
static t_binary *new_branche(t_binary *tree, char *str);
static void new_data(t_binary *tree, t_env *env);

void mini_parse(t_minishell *mini, char *str)
{
	//cree un maillon, malloc et rempli avec str
    mini->tree = new_branche(mini->tree, str);
    while (mini->tree->end != 1)
        nom_de_fonction(mini->tree, mini->env);

}

static void nom_de_fonction(t_binary *tree, t_env *env)
{
    new_data(tree, env);
    ft_printf("left -> %s\n", tree->command);
    ft_printf("right -> %s\n", tree->rest);
    if (tree->command == NULL)
    {
        tree->end = 1;
        return ;
    }
    tree->left = new_branche(tree->left, tree->command);
    tree->right = new_branche(tree->right, tree->rest);
	if (tree->left != NULL && tree->left->end != 1)
        nom_de_fonction(tree->left, env);
	else if (tree->right != NULL && tree->right->end != 1)
		nom_de_fonction(tree->right, env);
    ft_printf("end -> %d\n", tree->end);
	tree->end = 1;
}

static int search_command(char *str, t_env *env)
{
    int i;
    int j;
    char *cmd;

    i = 0;
    j = 0;
    while (str[i] != '\0')
    {
        while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
            i++;
        while (ft_isalpha(str[i]) <= 0)
            i++;
        while (ft_isalpha(str[i]) > 0)
        {
            i++;
            j++;
        }
        cmd = malloc ((sizeof (char *) * j ) + 1);
        i = i - j;
        j = 0;
        while (ft_isalpha(str[i]) > 0)
        {
            cmd[j] = str[i];
            i++;
            j++;
        }
        if (is_a_fonction(cmd,env) == 1)
        {
            return (i - j - 1);
        }
    }
    return (-1);
}

static t_binary *new_branche(t_binary *tree, char *str)
{
    tree = malloc(sizeof(t_binary));
    tree->data = str;
    tree->end = 0;
    tree->left = NULL;
    tree->right = NULL;
    tree->command = NULL;
    tree->rest = NULL;
    return (tree);
}

static void new_data(t_binary *tree, t_env *env)
{
    int next_cmd;
    int i;
    int j;

    i = 0;
    j = 0;
    next_cmd = search_command(tree->data, env);
    if (next_cmd == -1) {
        tree->end = 1;
        return;
    }
    tree->command = malloc(sizeof(char *) * next_cmd + 1);
    while (i <= next_cmd) {
        tree->command[i] = tree->data[i];
        i++;
    }
    tree->rest = malloc(sizeof(char *) * (ft_strlen(tree->data) - next_cmd) + 1);
    while (tree->data[i]) {
        tree->rest[j] = tree->data[i];
        i++;
        j++;
    }
    tree->rest[j] = '\0';
}