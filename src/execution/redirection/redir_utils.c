/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:40 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/17 12:15:30 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static	bool	is_a_redir_bis(int count_left, int count_right, int count_pipe);

bool	is_a_redir(char *cmd)
{
	int	pos;
	int	count_left;
	int	count_right;
	int	count_pipe;

	count_left = 0;
	count_right = 0;
	count_pipe = 0;
	pos = 0;
	while (cmd[pos])
	{
		if (cmd[pos] == '>')
			count_right++;
		else if (cmd[pos] == '<')
			count_left++;
		else if (cmd[pos] == '|' )
			count_pipe++;
		pos++;
	}
	return (is_a_redir_bis(count_left, count_right, count_pipe));
}

static	bool	is_a_redir_bis(int count_left, int count_right, int count_pipe)
{
	if (((count_right == 1) && (count_left == 0) && (count_pipe == 0))
		|| ((count_right == 1) && (count_left == 0) && (count_pipe == 1)))
		return (true);
	else if ((count_right == 2) && (count_left == 0) && (count_pipe == 0))
		return (true);
	else if ((count_left == 1 || count_left == 2) && (count_right == 0)
		&& (count_pipe == 0))
		return (true);
	else
		return (false);
}

bool	is_a_pipe(char *cmd)
{
	int	count_pipe;
	int	pos;

	count_pipe = 0;
	pos = 0;
	ft_printf("%s\n", cmd);
	while (cmd[pos])
	{
		if (cmd[pos] == '|' )
			count_pipe++;
		if (cmd[pos] == '>' && cmd[pos + 1] == '|')
		{
			count_pipe = -1;
			break ;
		}
		pos++;
	}
	if (count_pipe == -1)
	{
		ft_printf("salut\n");
		return (false);
	}
	if (count_pipe == 1)
		return (true);
	else
		return (false);
}

int	count_redir_in_pipe(char **cmd, int pos_before, int pos_after)
{
	int	count_left;
	int	count_right;

	count_left = 0;
	count_right = 0;
	while (pos_before <= pos_after)
	{
		if (cmd[pos_before][0] == '>')
			count_right++;
		else if (cmd[pos_before][0] == '<')
			count_left++;
		pos_before++;
	}
	if (count_right == 1)
		return (1);
	else if (count_right == 2)
		return (2);
	else if (count_left == 1)
		return (3);
	else
		return (0);
}

int	check_open(int file)
{
	if (file == -1)
		return (-1);
	return (0);
}
