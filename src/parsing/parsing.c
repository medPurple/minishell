
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

static int is_a_fonction(char *str,t_env *env);

void mini_parse(t_minishell *mini, char *str)
{
	if (is_a_fonction(str, mini->env) == 1)
		ft_printf("OK\n");
	else
		ft_printf("ko\n");
}


static int is_a_fonction(char *str,t_env *env)
{
	(void)str;
	char **split_env;
	char *tmp_env;
	char *join;
	char *search;
	t_env *tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	tmp = env;
	while (ft_strcmp(tmp->name,"PATH") != 0)
		tmp = tmp->next;
	while (tmp->data[i] != '=')
		i++;
	tmp_env = malloc(sizeof(char *) * (ft_strlen(tmp->data) - i));
	i++;
	while (tmp->data[i]) {
		tmp_env[j] = tmp->data[i];
		i++;
		j++;
	}
	split_env = ft_split(tmp_env, ':');
	i = 0;
	while(split_env[i])
	{
		join = ft_strjoin(split_env[i],"/");
		search = ft_strjoin(join,str);
		if (access(search, F_OK) == 0)
			return(1);
		i++;
	}
	return (0);

}