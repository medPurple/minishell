/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:10:00 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/22 16:49:07 by wmessmer         ###   ########.fr       */
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

extern int	g_eoat;
typedef struct s_wc
{
	char		*file;
	struct s_wc	*next;

}	t_wc;

typedef struct s_binary
{
	int						end;
	char					*data;
	char					*rest;
	char					*command;
	bool					parentheses;
	bool					status;
	int						previous_data;
	int						cmd_cr;
	int						par_base;
	struct s_cmd			*cmd;
	struct s_binary			*prev;
	struct s_binary			*left;
	struct s_binary			*right;
	struct s_redirection	*redir;
}				t_binary;

typedef struct s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_redirection
{
	char					*redir_cmd;
	char					*redir_file;
	int						ok;
	struct s_redirection	*next;

}				t_redirection;

typedef struct s_cmd
{
	char	*str;
	int		exec;
	char	**split_cmd;
	char	**exec_cmd;
	char	*path_cmd;
	pid_t	fork;
	pid_t	fork_pipe;
	int		pipe_fd[2];
	int		status;
	int		count;
	int		pipe_tmp;
	int		check_pipe;
	int		check;
	int		check_redir;
	int		check_here_doc;
	int		is_a_redir;
	int		fd[2];
	int		in;
	int		out;

}				t_cmd;

typedef struct s_minishell
{
	t_env		*env;
	t_binary	*tree;
	char		**envp;

}				t_minishell;

/*----------------------- ENVIRONNEMENT ------------------------*/
void			add_env(t_env **env, char **envp);

/*----------------------- PARSING ------------------------------*/
void			mini_parse(t_minishell *mini, char *str);
void			expand(t_binary *tree, t_env *env);
int				parsing(t_minishell *mini, char *str);
void			parse_data(t_binary *tree, t_env *env);
void			create_root(t_binary *tree, t_env *env);
t_binary		*new_branche(t_binary *tree, char *str);
int				find_next_quotes(char *str, int pos);
char			**removes_quotes(char **tab);
int				verif_parentheses(t_binary *tree);
bool			has_nothing(char *str);
char			*replace_doll_bis(char *str, t_env *env, int position, int i);
bool			need_split(char *str, int i);
int				expand_norme_2(t_binary *tree, int i);
int 			nome_e_doll(char *str, int i);


/*-----------------------EXECUTION------------------------------*/
void			exec_recu(t_minishell *mini, t_binary *tree);
void			exec_recu_norme(t_minishell *mini, t_binary *tree, int i);
void			exec_cmd_redir(t_binary *tree);
void			execute_cmd(t_binary *tree, t_minishell *mini);
char			**mini_split(char *str, int j, int i, int k);
void			create_cmd(t_binary *tree);
void			create_cmd_in_tree(t_binary *tree);
char			*cmd_recuperation(char *str, t_env *env);
void			mini_or(t_binary *tree, t_minishell *mini);
void			mini_and(t_binary *tree, t_minishell *mini);
int				cmd_redir_malloc(t_binary *tree, int i, int j, int save_pos);
void			execution_choice(t_binary *tree, t_minishell *mini);
void			exec_send(t_binary *tree, t_minishell *mini, int status, int i);
void			exec_meta( t_binary *tree, t_minishell *mini);
void			execution(t_minishell *mini, t_binary *tree);
void			execution_norme(t_minishell *mini, t_binary *tree, int i);
void			execution_norme_2(t_minishell *mini, t_binary *tree,
					int status);
bool			count_space_pipe(char *str, int pos);

/*---------------------------REDIRECTION--------------------------*/
void			pipex(t_binary *tree, t_minishell *mini, int i, int j);
void			last_pipex(t_binary *tree, t_minishell *mini, int i, int j);
void			pipe_redir(t_binary *tree);
void			check_redir_pipe(t_binary *tree);
void			open_file_pipe(t_binary *tree, int read, int write);
void			execution_choice_pipe(t_binary *tree, t_minishell *mini);
int				last_pipe_redir(t_binary *tree, int i);
void			mini_here_doc(char *limiter, t_binary *tree);
int				redir_is_valid(char *str);
void			initialize_pipe_value(t_binary *tree);
int				count_pipe(t_binary *tree);
void			pipe_option(t_binary *tree, int choice, int pos);
void			pipe_parent(t_binary *tree, int choice);
void			fork_option(t_minishell *mini, t_binary *tree,
					int choice, int i);
void			wait_child(t_binary *tree);
void			pipe_reduce(t_binary *tree);
int				is_a_redir_or_pipe(char *str, int start, int end);
int				is_a_redir_or_pipe_bis(int count_left, int count_right,
					int count_pipe);
void			mini_here_doc_norme(t_binary *tree, int i);

/*------------------------BUILD-IN------------------------------*/
void			exec_buildin(t_binary *tree, t_minishell *mini);
void			exec_buildin_child(t_binary *tree, t_minishell *mini);
void			mini_echo(t_binary *tree);
void			mini_exit(t_minishell *mini, char *str, t_binary *tree);
void			clear_the_tree(t_binary *tree);
void			mini_pwd(t_env *env, t_binary *tree);
void			mini_cd(t_env *env, t_binary *tree);
void			cd_norme(char *str, t_env *env);
void			cd_norme_2(char *str, char *cmd, t_env *env);
void 			cd_norme_3(char *str, t_binary *tree, t_env *env, int j);
void			changedir(char *destination, t_env *env, char *old, char *dest);
void			mini_env(t_env *env);
void			mini_export(t_env **env, char **tab);
void			mini_unset(t_env **env, char **tab);
char			*get_status(t_binary *tree);
bool			open_close(char *str);
char			*find_dir(t_env *env);
int				count_arg(char **tab, int j);

/*----------------------SIGNALS----------------------------------*/
void			signal_ctrlc(int sig);
void			print_binary(t_binary *tree);

/*----------------- UTILS - environnement ------------------------*/
t_env			*ft_new_element(char *data);
t_env			*ft_last_lst(t_env *lst);
void			ft_add_back_lst(t_env **lst, t_env *new);

/* -------------- UTILS - parsing ------------------------------- */
void			ignore_parentheses(t_binary *tree, int para_count);
void			replace_parentheses(t_binary *tree, t_env *env);
int				end_of_quotes(char *str, int i);
bool			is_a_meta(char *str, int i);
int				pass_quotes(char *str, int i);
int				is_a_fonction(char *str, t_env *env);
int				is_a_buildin(char *str);
void			split_char(t_binary *tree);
int				find_next_split(t_binary *tree, t_env *env);
bool			string_analyse(t_binary *tree, char *str, t_env *env);
int				split_pos(t_binary *tree, char *str, int i);
int				end_of_parentheses(char *str, int position);
char			*join_all_part(char *str, char *add);
char			*sie_norme(t_env *tmp, char *str);
char			*jap_norme(char *str, int i, char *before, char *add);
char			*jap_norme_2(char *str, char *af, char *bf, int i);
int				ipp_norme(char *str);
char			*rmq_norme(char *tab);
int				fns_norme(char *str, int i);
int				ipp_norme_2(char *str, int i);
int				verif_meta(t_binary *tree);
bool			is_letter(char c);
int				norme_sp(int i, char *str, int j);

/*-------------------Wildcards-------------------------------*/
char			*wildcard(char *str, int i);
void			wc_addback(t_wc **list, t_wc *new);
t_wc			*new_wc(char *str);
bool			first_letter(char *str, char *ex);
bool			last_letter(char *str, char *ex);
char			**wc_before_and_after(char *bfwc, char *afwc, t_wc *file);
int				bf_af_norme(t_wc *tmp, char *bfwc, char *afwc);
int				af_norme(t_wc *tmp, char *afwc);
int				bf_norme(t_wc *tmp, char *bfwc);
char			**wc_all(t_wc *file);
char			**wc_after(char *afwc, t_wc *file);
char			**wc_before(char *bfwc, t_wc *file);
char			*ft_strjoat(char *s1, char *s2);
char			*put_in_quotes(char *begin, char *end, char *bfwc, char *afwc);

/*--------------------Parentheses------------------------------*/
void			expand_parentheses_and_execute(t_binary *tree,
					t_minishell *mini);
void			exec_recu_par(t_minishell *mini, t_binary *tree);
void			exec_meta_par( t_binary *tree, t_minishell *mini);
void			mini_or_par(t_binary *tree, t_minishell *mini);
void			mini_and_par(t_binary *tree, t_minishell *mini);

/*---------------UTILS - execution----------------------------*/
int				check_open(int file);
bool			is_a_redir(char *cmd);
bool			is_a_pipe(char *cmd);
int				is_here_doc(t_binary *tree);
int				count_redir_right(t_binary *tree);
int				count_redir_left(t_binary *tree);
int				count_redir_right_double(t_binary *tree);
void			open_file(t_binary *tree);
t_redirection	*ft_new_redirection(char *redir, char *file, int j);
t_redirection	*ft_last_lst_redirection(t_redirection *lst);
void			ft_add_back_lst_redirection(t_redirection **lst,
					t_redirection *new);
void			ft_free_lst(t_redirection *stack);
void			mini_error_one(int i);
int				verif_redir(t_binary *tree, int left, int right, int save_pos);
int				verif_redir_norme(t_binary *tree);
int				redir_error(char *str, int left, int right, int save_pos);
bool			count_space(char *str, int pos);
int				pipe_is_valid(char **str);

#endif
