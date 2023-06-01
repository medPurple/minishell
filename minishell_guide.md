# Explications du parsing

# Sommaire

- [Explications de la structure](#explications-de-la-structure)
- [Explications des fonctions](#explications-des-fonctions)
    - [new_branche](#new_branche)
    - [parse_test](#parse_test)
    - [parse_data](#parse_data)
    - [split_char](#split_char)
    - [create_root](#create_root)
    - [find_next_split](#find_next_split)
    - [string_analyse](#string_analyse)
    - [split_pos](#split_pos)
    - [ignore_parentheses](#ignore_parentheses)
    - [end_of_quotes](#end_of_quotes)
    - [is_a_meta](#is_a_meta)
    - [pass_quotes](#pass_quotes)
    - [is_a_meta](#is_a_meta)
    - [pass_quotes](#pass_quotes)
	- [execution](#execution)


## Explications de la structure
 Le principe est le meme que celui utilisé précedement. On crée un arbre binaire et on analyse une string pour cree des maillons.
La difference c'est que désormais on observe les premiers charactères de la string afin de savoir si on a une parenthese.
Si c'est le cas on split, sinon on utilise une fonction d'analyse pour analyser une partie de la string. ( string split par des espaces)
Si l'analyse renvoie -1, on a fini de parser la string, sinon on split a la position renvoyée par l'analyse.
cette analyse cherche les metacharactères, les quotes, les buildins et les fonctions et traite differement chaque cas.

Si tu as eu le courage de lire jusque la sache que apres relecture j'ai juste reformulé ce que tu avais deja codé. Donc en vrai c'est un peu ton code,
dis d'une autre facon. Bref j'aime bien ecrire juste pour ecrire et je suppose que tu vas lire ça en diagonal car tu aura surement scroller jusqu'au fonction sans lire tout ca.
ou alors peut etre que je suis arrivé entre temps et que je t'ai distrais en racontant ma vie ou en ecoutant la tienne.
Bref je vais arreter d'ecrire et te laisser lire le code, car github copilot veut absolument que je t'envoie lire mon code ahah, il me le propose en premanance.

## Explications des fonctions

### new_branche
Meme fonction que celle utilisée precedement, crée juste un maillon vide.

```
static t_binary *new_branche(t_binary *tree, char *str)
{
  tree = malloc(sizeof(t_binary));
  tree->data = str;
  tree->end = 0;
  tree->prev = NULL;
  tree->left = NULL;
  tree->right = NULL;
  tree->command = NULL;
  tree->rest = NULL;
  return (tree);
}
```
### parse_test
Fonction principale appellant la recursion.
```
void parse_test(t_minishell *mini, char *str)
{
	mini->tree = new_branche(mini->tree, str);
	while (mini->tree->end != 1)
		parse_data(mini->tree, mini->env);
}
```

### parse_data
Meme fonction que celle utilisée precedement, crée et rempli des branches
```
static void parse_data(t_binary *tree, t_env *env)
{
	if (tree->left == NULL)
		create_root(tree, env);
	if (tree->command == NULL) {
			tree->end = 1;
			return;
	}
	tree->left = new_branche(tree->left, tree->command);
	tree->right = new_branche(tree->right, tree->rest);
	ft_printf ("\n\ntree left = %s |||| ", tree->left->data);
	ft_printf ("tree right = %s \n", tree->right->data);
	tree->right->prev = tree;
	tree->left->prev = tree;
	if (tree->right != NULL && tree->right->end != 1)
		parse_data(tree->right, env);
	if (tree->right->end == 1)
		tree->end = 1;
}
```
### split_char
Nouvelle fonction a ameliorer, elle separe la chaine avant le  metacharactere mais ne verifie pas que le metacharactere exite
( ex &|)
```
static void split_char(t_binary *tree)
{
	int i;

	i = 0;
	while (is_a_meta(tree->data[i]) == true)
		i++;
	tree->command = ft_limited_strdup(tree->data,0,i);
	tree->rest = ft_limited_strdup(tree->data,i+1, ft_strlen(tree->data));
}
```
### create_root
Fonction qui va creer la racine de l'arbre, elle va appeler la fonction ignore parentheses is la string commence par une parenthese, split_char si le premier caractere est un metacharactere, sinon elle va appeler find_next_split pour trouver le prochain metacharactere.

```
static void create_root(t_binary *tree, t_env *env)
{
	int split;

	if (tree->data[0] == '(')
		ignore_parentheses(tree);
	else if (is_a_meta(tree->data[0]) == true)
		split_char(tree);
	else{
		split = find_next_split(tree, env);
		if (split == -1)
			return;
		else
		{
			tree->command = ft_limited_strdup(tree->data,0,split);
			tree->rest = ft_limited_strdup(tree->data,split + 1, ft_strlen(tree->data));
		}
		return;
	}
}
```
### find_next_split
Fonction qui va analyser chaque partie la string partie par partie. Si on a une quotes au debut, elle ignore son contenue. elle recupere les mots entre chaque espace,
et les envoi dans string_analyse, afin de verifier si la partie analysée est une fonction, un buildin ou si elle contient des metacharactères.
Si elle ne contient pas de metacharactere, elle passe a la partie suivante. Sinon, elle recuperela position du prochain split dans cette partie.
Si rien n'est trouvé, elle renvoie -1 le parsing est terminé.
```
static int find_next_split(t_binary *tree, t_env *env)
{
	int i = 0;
	int j = 0;
	char *str;

	while(tree->data[i] != '\0')
	{

		while(tree->data[i] != '\0' && tree->data[i] != ' ' && tree->data[i] != '\t')
		{
			if (tree->data[i] == '\'' || tree->data[i] == '\"')
				i = end_of_quotes(tree->data, i);
			else
				i++;
		}
		str = ft_limited_strdup(tree->data, j, i - 1);
		if (string_analyse(str,env) != true)
		{
			free(str);
			while ((tree->data[i] == ' ' || tree->data[i] == '\t') && tree->data[i] != '\0')
				i++;
			j = i;
		} else
		{
			if (j == 0 && (is_a_fonction(str, env) || is_a_buildin(str))) {
				free(str);
				while ((tree->data[i] == ' ' || tree->data[i] == '\t') && tree->data[i] != '\0')
					i++;
				j = i;
			}
			else
				return(split_pos(tree->data, env, j, i - 1));
		}

		if (tree->data[i] == '\0')
			return (-1);
	}
	return (-1);
}
```
### string_analyse
Fonction qui analyse la string. si l'ensemble est une fonction ou un buildin, elle renvoie true.
Sinon, elle parcours la string, si elle trouve une quote, elle ignore son contenu grace a end_of_quotes qui avance i jusqu'a la fin des quotes.
Si elle trouve un metacharactere, elle renvoie true.
```
static bool string_analyse(char *str, t_env *env)
{
	int i = 0;

	if (is_a_fonction(str, env) || is_a_buildin(str))
		return(true);
	else
	{
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				i = end_of_quotes(str, i);
			else{
				if((str[i]) == '(' || str[i] == '&' || str[i] == '|' || str[i] == '<' || str[i] == '>')
					return (true);
				i++;
			}
		}
		return(false);
	}
}
```
### split_pos
Cherche la position a laquelle split. Si str est une fonction ou un buildin, elle renvoi la position du caractere precedent str.
Sinon, elle parcourt la string. 
Si elle trouve une quote, elle ignore son contenu grace a end_of_quotes qui avance i jusqu'a la fin des quotes.
Si elle trouve un metacharactere, elle renvoie la position du caractere precedent le metacharactere.
```
static int split_pos(char *str, t_env *env, int j, int i)
{
	char *str_a = ft_limited_strdup(str, j, i);
	if (is_a_fonction(str_a, env) || is_a_buildin(str_a))
	{
		return(j - 1);
	}
	else
	{
		i = j;
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				i = end_of_quotes(str, i);
				return (i - 1);
			}
			else {
				if ((str[i]) == '(' || str[i] == '&' || str[i] == '|' || str[i] == '<' || str[i] == '>')
					return (i - 1);
				i++;
			}
		}
	}
	return (-1);

}
```
### ignore_parentheses
Fonction identique a la tienne qui ignore les parentheses en comptant combien elle en rencontre.
Amelioration possible en prenant en compte les parentheses dans les quotes.
```
static void ignore_parentheses(t_binary *tree)
{
	int i = 1;
	int para_count = 1;

	while (para_count != 0)
	{
		if (tree->data[i] == '\0')
			break;
		if (tree->data[i] == ')')
			para_count--;
		else if (tree->data[i] == '(')
			para_count++;
		i++;
	}
	if (i != (int)ft_strlen(tree->data))
	{
		tree->command = ft_limited_strdup(tree->data, 0, i);
		tree->rest = ft_limited_strdup(tree->data, i+1, ft_strlen(tree->data));
	} else
		return;
}
```
### end_of_quotes
Fonction qui permet d'ignorer le contenu des quotes. Elle utilise une recursion pour ignorer les quotes dans les quotes.
Une fois la quote fermee, elle avance i jusqu'a rencontrer un metacharactere et renvoie la position.
Amelioration possible en modifiant la condition de sortie des boucles pour prendre en compte \0
```
static int end_of_quotes(char *str, int i)
{
	char c;

	c = str[i];
	i++;
	while (str[i] != c)
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
		else
			i++;
	}
	i++;
	while (is_a_meta(str[i]) != true)
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
		else
			i++;
	}
	return (i);

}
```
### is_a_meta
Verifie si le caractere est un metacharactere.
```
static bool is_a_meta(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (true);
	else
		return (false);
}
```
### pass_quotes
Fonction recurisve qui permet d'ignorer les quotes dans les quotes.
```
static int pass_quotes(char *str, int i)
{
	char c;

	c = str[i];
	while(str[i] != c)
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
		i++;
	}
	return (i);
}
```

## Execution

1/ Verifier les priorites (ou pas, cf discussion d hier 31/05 au sujet de l'execution dans l'ordre de lecture)
2/ Executer les maillons le plus a gauche possible ou, le cas echeant, celui de droite. (autrement dit aller le plus a gauche possible puis executer gauche et droite, puis remonter d un cran, executer gauche et droite et ainsi de suite) + marquer ceux qui ont ete executes
Note : gestion des () et des && - ||
	si && et que la commande 1 est fausse, ne rien executer du tout 
	si && et que la commande 2 ou suivantes est / sont fausses alors execute jusqu'a rencontrer une commande fausse
	si || executer la 1 si Ok ou executer la 2 si 1 est KO (si plusieurs, executer la premiere qui fonctionne)
3/ Redirection 

Note : faire un split perso afin de ne pas split les espace lorsqu'il y a des arguments entre quotes. 
	traiter les quotes en fonction des espaces ou absence d'espace. Autrement dit, si 0 espace ( ex : ls "-l") faire comme s'il n'y avait pas de quotes sinon ne pas interpreter ( ex : ls "  -l").
	