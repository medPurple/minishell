/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:10:00 by mvautrot          #+#    #+#             */
/*   Updated: 2023/05/15 10:49:59 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
//ls -l && echo 'test > FILE' > FILE && cat FILE
//ls "-l" -la && (cat salut) || cat coucou
//ls (-l) -la && (cat salut) || cat coucou
//(ls -ls) && cat file || ls "-l -ls (test)" -la | (test) | file
// est ce qu on creer un arbre binaire a partir de ce qui a ete creer initialement
//autrement dit repartir de ce qui existe et rediviser a partir des quotes

typedef struct s_binary
{
	int	end;
	char *data;
    char *rest;
    char *command;
	struct s_binary *prev;
	struct s_binary *left;
	struct s_binary *right;
}           t_binary;

typedef struct s_env
{
	char	*name;
	char	*data;
	struct s_env	*next;
}				t_env;

typedef struct s_minishell
{
	t_env	*env;
	t_binary *tree;

}				t_minishell;

/*--------------------------------------- ENVIRONNEMENT -------------------------------------------*/

void add_env(t_env **env, char **envp);
void mini_export(t_env *env, char *str);

/*---------------------------------------- PARSING ------------------------------------------------*/

void mini_parse(t_minishell *mini, char *str);

/*-------------------------------------- UTILS - ENV ----------------------------------------------*/
t_env	*ft_new_element(char *data);
t_env	*ft_last_lst(t_env *lst);
void	ft_add_back_lst(t_env **lst, t_env *new);

/* ------------------------------------ UTILS - parsing ------------------------------------------- */
int	search_data(char *str, t_env *env);
int is_a_fonction(char *str,t_env *env);
int search_command(char *str, t_env *env, int limit);
int	is_a_metacharacters(char *str, t_env *env, int limit);
int	is_a_quotes(char *str, t_env *env);
int	is_a_characters(char *str, int limit);
int	is_a_redirection(char *str);
int	is_a_pipe_or_else(char *str);
int is_a_and(char *str);
int	is_a_parenthesis (char *str);
int is_a_buildin(char *str);



#endif
