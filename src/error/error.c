/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:05:49 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/11 15:18:11 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static void mini_error_two(int i);
static void mini_error_three(int i);
static void mini_error_four(int i);
static void mini_error_five(int i);


void mini_error_one(int i)
{
	if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else
		mini_error_two(i);
}

static void mini_error_two(int i)
{
	if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else
		mini_error_three(i);
}

static void mini_error_three(int i)
{
	if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else
		mini_error_four(i);
}

static void mini_error_four(int i)
{
	if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else
		mini_error_five(i);
}

static void mini_error_five(int i)
{
	if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else if (i == 0)
	{
		g_eoat = 0;
		send_error("TEST\n");
	}
	else
		send_error("[Unknown error]\n");
}
