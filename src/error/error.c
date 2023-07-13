/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:05:49 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/12 11:32:33 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	mini_error_two(int i);
static void	mini_error_three(int i);
static void	mini_error_four(int i);
static void	mini_error_five(int i);

void	mini_error_one(int i)
{
	if (i == 1)
	{
		g_eoat = 2;
		send_error("minishell: syntax error near unexpected token 'newline'\n");
	}
	else if (i == 2)
	{
		g_eoat = 2;
		send_error("minishell: syntax error near unexpected token '>'\n");
	}
	else if (i == 3)
	{
		g_eoat = 2;
		send_error("minishell: syntax error near unexpected token '>>'\n");
	}
	else if (i == 4)
	{
		g_eoat = 2;
		send_error("minishell: syntax error near unexpected token '|'\n");
	}
	else
		mini_error_two(i);
}

static void	mini_error_two(int i)
{
	if (i == 5)
	{
		g_eoat = 2;
		send_error("minishell: syntax error near unexpected token '||'\n");
	}
	else if (i == 6)
	{
		g_eoat = 2;
		send_error("minishell: syntax error near unexpected token '<'\n");
	}
	else if (i == 7)
	{
		g_eoat = 2;
		send_error("minishell: syntax error near unexpected token '<'\n");
	}
	else if (i == 8)
	{
		g_eoat = 126;
		send_error("minishell: Is a directory\n");
	}
	else
		mini_error_three(i);
}

static void	mini_error_three(int i)
{
	if (i == 9)
	{
		g_eoat = 127;
		send_error("minishell: command not found\n");
	}
	else if (i == 10)
	{
		g_eoat = 2;
		send_error("minishell: syntax error near unexpected token '&&'\n");
	}
	else if (i == 11)
	{
		g_eoat = 127;
		send_error("minishell: No such file or directory\n");
	}
	else if (i == 12)
	{
		g_eoat = 126;
		send_error("minishell: Permission denied\n");
	}
	else
		mini_error_four(i);
}

static void	mini_error_four(int i)
{
	if (i == 13)
	{
		g_eoat = 1;
		send_error("minishell: export : not a valid identifier\n");
	}
	else if (i == 14)
	{
		g_eoat = 1;
		send_error("minishell: unset : not a valid identifier\n");
	}
	else if (i == 15)
	{
		g_eoat = 1;
		send_error("minishell: invalid option\n");
	}
	else if (i == 16)
	{
		g_eoat = 1;
		send_error("minishell: too many arguments\n");
	}
	else
		mini_error_five(i);
}

static void	mini_error_five(int i)
{
	if (i == 17)
	{
		g_eoat = 0;
		send_error("minishell: cd: HOME not set\n");
	}
	else if (i == 18)
	{
		g_eoat = 1;
		send_error("minishell: chdir: error retrieving current directory: \
		getcwd: cannot access parent directories: No such file or directory\n");
	}
	else if (i == 19)
	{
		g_eoat = 2;
		send_error("minishell: exit: numeric argument required\n");
	}
	else if (i == 20)
	{
		g_eoat = 2;
		send_error("minishell: syntax error near unexpected token ')'\n");
	}
	else
		send_error("[Unknown error]\n");
}
