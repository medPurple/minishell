/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisplit_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:10:37 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/12 17:11:38 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_a_redir_or_pipe(char *str, int start, int end)
{
	int	count_left;
	int	count_right;
	int	count_pipe;
	int	check;

	count_left = 0;
	count_right = 0;
	count_pipe = 0;
	while (start < end)
	{
		if (str[start] == '>')
			count_right++;
		else if (str[start] == '<')
			count_left++;
		else if (str[start] == '|' )
			count_pipe++;
		start++;
	}
	check = is_a_redir_or_pipe_bis(count_left, count_right, count_pipe);
	return (check);
}

int	is_a_redir_or_pipe_bis(int count_left, int count_right,
		int count_pipe)
{
	if ((count_right == 1) && (count_left == 0) && (count_pipe == 0))
		return (1);
	else if ((count_right == 2) && (count_left == 0) && (count_pipe == 0))
		return (2);
	else if ((count_left == 1) && (count_right == 0) && (count_pipe == 0))
		return (1);
	else if ((count_left == 2) && (count_right == 0) && (count_pipe == 0))
		return (2);
	else if ((count_left == 0 || count_left == 0)
		&& (count_right == 0) && (count_pipe == 1))
		return (1);
	else
		return (-1);
}
