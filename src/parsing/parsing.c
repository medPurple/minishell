
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

static void nom_de_fonction(t_binary *tree, char *str);

void mini_parse(t_minishell *mini, char *str)
{
	//cree un maillon, malloc et rempli avec str
	nom_de_fonction(mini->tree, str);

}

static void nom_de_fonction(t_binary *tree, char *str)
{
	int fin_phrase;
	int i;
	int j;
	char *str_cmd;
	char *reste;


	fin_phrase = search_cmmand(str);
	str_cmd = malloc (fin_phrase + 1);
	while ( i != fin_phrase)
		str_cmd[i] = str[i];
	reste = malloc (strlen(str - fin_phrase) + 1);
	while (str[i])
		reste[j] = str[i];
	new_maillon(str_cmd,reste); // contient string gauche et reste droite
	// new maillon cree les maillon droite et gauche ( 2x new elem)
	if (tree->left != NULL && tree->left->end != 1)
		nom_de_fction(tree->left, tree->left->data);
	else if (tree->right != NULL && tree->right->end != 1)
		nom_de_fonction(tree->right, tree->right->data);
	tree->end = 1;



}
