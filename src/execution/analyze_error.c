/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 09:26:26 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/21 15:40:54 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//static int	nb_redir(t_binary *tree, int count_right, int count_left, int i);
//static int	analyze_error_bis(t_binary *tree, int count);
static int redir_error(char *str, int left, int right, int i, int save_pos);

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
			//ft_printf("test\n");
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
			//ft_printf ("%i", right);
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
	if (save_pos != 0)
		save_pos--;
	//ft_printf ("str :  %c\n %ctame\n", str[save_pos +1], str[save_pos]);
	if (str[0] == '>' && str[1] == '|' && str[2] == '\0')
	{
		mini_error_one(1);
		return(-1);
	}
	if (str[i] !='\0' && str[i] != '>' && str[i] != '<' && ((right < 3 && left == 0) || (right == 0 && left < 3)))
		return (0);
	else
	{
		//ft_printf("test\n");
		if (str[save_pos] == '>' && str[save_pos + 1] == '<')
			mini_error_one(6);
		else if (str[0] == '>' && str[1] == '|')
			mini_error_one(1);
		else if (str[save_pos] == '|')
			mini_error_one(4);
		else if (left == 1 || right == 1)
			mini_error_one(1);
		else if ((left == 2 || right == 2))
			mini_error_one(1);
		else if (left == 3)
			mini_error_one(1);
		else if (right == 3 || (right == 2 && str[save_pos] == '>' && str[save_pos + 1] != '>'))
			mini_error_one(2);
		else if (left == 4)
			mini_error_one(6);
		else if (right >= 4)
			mini_error_one(3);
		else if (left == 5)
			mini_error_one(7);
		else if (left >= 6)
		{
			g_eoat = 2;
			send_error("minishell: syntax error near unexpected token `<<<'\n");
		}
		return (-1);
	}
	return (0);
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
