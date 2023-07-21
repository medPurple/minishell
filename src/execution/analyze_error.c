/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 09:26:26 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/21 18:26:47 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int redir_error(char *str, int left, int right, int i, int save_pos);
bool count_space(char *str, int pos);

int verif_redir(t_binary *tree)
{
	int	left;
	int	right;
	int	i;
	int	save_pos;

	i = 0;
	save_pos = 0;

	if (!(tree->data))
		return (-1);
	while (tree->data[i])
	{
		left = 0;
		right = 0;
		if (tree->data && (tree->data[i] == '<' || tree->data[i] == '>'))
		{
			save_pos = i;
			if (tree->data[i] == '<')
			{
				while (tree->data[i] == '<')
				{
					left++;
					i++;
				}
			}
			if (tree->data[i] == '>')
			{
				while (tree->data[i] == '>')
				{
					right++;
					i++;
				}
			}
			if (redir_error(tree->data, left, right, i, save_pos) < 0)
			 	return (-1);
		}
		i++;
	}
	if (tree->right)
	{
		if (verif_redir(tree->left) == -1)
			return (-1);
		if (verif_redir(tree->right) == -1)
			return (-1);
	}
	return (0);
}

static int redir_error(char *str, int left, int right, int i, int save_pos)
{
	int	tmp;
	(void)i;
	tmp	= save_pos;
	if (save_pos != 0)
		save_pos--;
	if (str[tmp] == '<' && str[tmp + 1] == '<' && count_space(str, tmp + 2) == false)
		return (0);
	if (str[tmp] == '>' && str[tmp + 1] == '|' && count_space(str, tmp + 2) == false)
		return (0);
	else
	{
		if (str[save_pos] == '>' && str[save_pos + 1] == '<')
			return (mini_error_one(6), -1);
		else if (str[0] == '>' && str[1] == '|')
			return (mini_error_one(1), -1);
		else if (str[save_pos] == '|')
			return (mini_error_one(4), -1);
		else if ((right == 1 || left == 1))
			return (mini_error_one(1), -1);
		else if ((left == 2 || right == 2))
			return (mini_error_one(1), -1);
		else if (left == 3)
			return (mini_error_one(1), -1);
		else if (right == 3 || (right == 2 && str[save_pos] == '>' && str[save_pos + 1] != '>'))
			return (mini_error_one(2), -1);
		else if (left == 4)
			return (mini_error_one(6), -1);
		else if (right >= 4)
			return (mini_error_one(3), -1);
		else if (left == 5)
			return (mini_error_one(7), -1);
		else if (left >= 6)
		{
			g_eoat = 2;
			return (send_error("minishell: syntax error near unexpected token `<<<'\n"), -1);
		}
		return (0);
	}
	return (0);
}

bool count_space(char *str, int pos)
{
	int	i;
	if (pos > (int)ft_strlen(str))
		return (true);
	if (str[pos] && str[pos + 1] && str[pos + 2])
		i = pos + 1;
	else
		i = pos;
	while (str[i] && str[i] != '<' && str[i] != '>')
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

int	pipe_is_valid(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '|' && str[i + 1] == NULL)
				return (-1);
			if (str[i][j] == '|' && str[i + 1][j] == '|')
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}
