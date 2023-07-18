/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:16:00 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/18 16:51:05 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int check_option(char **str);

void	mini_pwd(t_env *env, t_binary *tree)
{
	char	*str;

	(void)env;
	str = getcwd(NULL, 0);
	if (str == NULL)
		mini_error_one(18);
	else if (check_option (tree->cmd->exec_cmd) > 0)
		ft_printf("minishell: pwd: invalid option\n");
	else
	{
		ft_printf("%s\n", str);
		free(str);
	}
}

static int check_option(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(str[i][0] == '-')
			return(1);
		i++;
	}
	return (0);
}
