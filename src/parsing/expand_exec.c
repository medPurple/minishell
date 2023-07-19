/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:51:57 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/18 18:19:17 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//if (tree->status == true)
//					tree->cmd->split_cmd = mini_split(get_status(tree), 0, 0, 0);

char **expand_bis(t_binary *tree)
{
	char **tab;
	int		i;

	i = 0;
	tab = NULL;
	//for (int k=0; tree->cmd->split_cmd[k]; k++)
	//	ft_printf("%s\n",tree->cmd->split_cmd[k]);
	if (tree->status == true)
		tree->cmd->split_cmd = mini_split(get_status(tree), 0, 0, 0);
	//for (int k=0; tree->cmd->split_cmd[k]; k++)
	//	ft_printf("%s\n",tree->cmd->split_cmd[k]);
	//while (tree->cmd->split_cmd[i])
	//{
	//	if (tree->cmd->split_cmd[i][0] == '$')
	//		ft_printf("OK - %s\n",tree->cmd->split_cmd[i]);
	//	i++;
	//}
	return (tab);
}