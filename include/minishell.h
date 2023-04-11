/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:10:00 by mvautrot          #+#    #+#             */
/*   Updated: 2023/04/05 14:11:04 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_command
{

    char **all;
    char **arguments;
    char *command;
    int pipe;
    int and;
    int or;
} t_command;

typedef struct *s_env
{
    char **envp;
} *t_env;
#endif
