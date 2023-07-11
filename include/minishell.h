/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:10:00 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/11 15:47:07 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>

typedef struct s_wc
{
	char *file;
	struct s_wc *next;

}	t_wc;

typedef struct s_binary
{
	int	end;
	char *data;
    char *rest;
    char *command;
	bool	parentheses;
	struct s_cmd *cmd;
	struct s_binary *prev;
	struct s_binary *left;
	struct s_binary *right;
	struct s_redirection	*redir;
}           t_binary;

typedef struct s_env
{
	char	*name;
	char	*data;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef	struct s_redirection
{
	char	*redir_cmd;
	char	*redir_file;
	int	ok;
	struct s_redirection	*next;

}				t_redirection;

typedef struct s_cmd
{
	char    *str;
	int    exec;
	char    **split_cmd;
	char	**exec_cmd;
    char    *path_cmd;
    pid_t   fork;
	pid_t	fork_pipe;
	int		pipe_fd[2];
	int	pipe_tmp;
	int	check_pipe;
	int	open_ko;
	int	check_here_doc;
	int	is_a_redir;
    int     fd[2];
    int     in;
    int     out;

}            t_cmd;

typedef struct s_minishell
{
	t_env	*env;
	t_binary *tree;
	char **envp;

}				t_minishell;

int	g_eoat = 0;

/*--------------------------------------- ENVIRONNEMENT -------------------------------------------*/

void add_env(t_env **env, char **envp);

/*---------------------------------------- PARSING ------------------------------------------------*/

void mini_parse(t_minishell *mini, char *str);
void expand(t_binary *tree, t_env *env);
int parsing(t_minishell *mini, char *str);
void parse_data(t_binary *tree, t_env *env);
void create_root(t_binary *tree, t_env *env);
t_binary *new_branche(t_binary *tree, char *str);
int	find_next_quotes (char *str, int pos);
char **removes_quotes(char **tab);
int verif_parentheses(t_binary *tree);
bool has_nothing(char *str);
/*------------------------------------------EXECUTION----------------------------------------------*/

void exec_recu(t_minishell *mini, t_binary *tree);
void exec_cmd_redir(t_binary *tree);
void execute_cmd(t_binary *tree, t_minishell *mini);
char **mini_split(char *str);
void create_cmd(t_binary *tree);
void create_cmd_in_tree(t_binary *tree);
char *cmd_recuperation(char *str, t_env *env);
void mini_or(t_binary *tree, t_minishell *mini);
void mini_and(t_binary *tree, t_minishell *mini);
int cmd_redir_malloc(t_binary *tree, int i);
void	execution_choice(t_binary *tree, t_minishell *mini);
void    exec_send(t_binary *tree, t_minishell *mini);


/*----------------------------------------------REDIRECTION----------------------------------------*/

void    pipex(t_binary *tree, t_minishell *mini);
void    last_pipex(t_binary *tree, t_minishell *mini, int i, int j);
void	pipe_redir(t_binary *tree);
void	check_redir_pipe (t_binary *tree);
void	open_file_pipe(t_binary *tree);
void	execution_choice_pipe(t_binary *tree, t_minishell *mini);
void	execute_cmd_pipe(t_binary *tree, t_minishell *mini);
int	last_pipe_redir(t_binary *tree, int i);
void	mini_here_doc(char *limiter, t_binary *tree);
int redir_is_valid(char *str);

/*------------------------------------------BUILD-IN-----------------------------------------------*/
void exec_buildin(t_binary *tree, t_minishell *mini);
void exec_buildin_child(t_binary *tree, t_minishell *mini);

void mini_echo(t_binary *tree);
void mini_exit(t_minishell *mini);
void clear_the_tree(t_binary *tree);
void mini_pwd(t_env *env);
void mini_cd(t_env *env, t_binary *tree);
void mini_env(t_env *env);
void mini_export(t_env **env, char **tab);
void  mini_unset(t_env **env, char **tab);

/*------------------------------------------SIGNALS----------------------------------------------*/

void    signal_ctrlc(int sig);
void print_binary(t_binary *tree);


/*-------------------------------------- UTILS - environnement ----------------------------------------------*/
t_env	*ft_new_element(char *data);
t_env	*ft_last_lst(t_env *lst);
void	ft_add_back_lst(t_env **lst, t_env *new);

/* ------------------------------------ UTILS - parsing ------------------------------------------- */
void ignore_parentheses(t_binary *tree);
void replace_parentheses(t_binary *tree, t_env *env);
int end_of_quotes(char *str, int i);
bool is_a_meta(char *str, int i);
int pass_quotes(char *str, int i);
int is_a_fonction(char *str,t_env *env);
int is_a_buildin(char *str);
void split_char(t_binary *tree);
int find_next_split(t_binary *tree, t_env *env);
bool string_analyse(char *str, t_env *env);
int split_pos(char *str, int i);
int end_of_parentheses(char *str, int position);

/*--------------------------------------Wildcards------------------------------------------------*/

char *wildcard(char *str, int i);
void wc_addback(t_wc **list, t_wc *new);
t_wc *new_wc(char *str);
bool first_letter(char *str, char *ex);
bool last_letter(char *str, char *ex);
char **wc_before_and_after(char *bfwc, char *afwc, t_wc *file);
char **wc_all(t_wc *file);
char **wc_after(char *afwc, t_wc *file);
char **wc_before(char *bfwc, t_wc *file);
char	*ft_strjoat(char *s1, char *s2);
char *put_in_quotes(char *begin, char *end, char *bfwc, char *afwc);

/*--------------------------------------Parentheses----------------------------------------------*/
void expand_parentheses_and_execute(t_binary *tree, t_minishell *mini);

/*------------------------------------------UTILS - execution----------------------------------------------*/

int	check_open(int	file);
bool is_a_redir(char *cmd);
bool is_a_pipe(char *cmd);
int	is_here_doc(t_binary *tree);
int	count_redir_right(t_binary *tree);
int	count_redir_left(t_binary *tree);
int	count_redir_right_double(t_binary *tree);
void	open_file(t_binary *tree);
t_redirection	*ft_new_redirection(char *redir, char *file);
t_redirection	*ft_last_lst_redirection(t_redirection *lst);
void	ft_add_back_lst_redirection(t_redirection **lst, t_redirection *new);
void	ft_free_lst(t_redirection *stack);
void	dup2_fd(int fd, int fd2);

/*---------------------------------------------ERROR-------------------------------------------------------*/

void mini_error_one(int i);

#endif
