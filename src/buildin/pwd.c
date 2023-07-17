/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:16:00 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/17 15:45:09 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mini_pwd(t_env *env)
{
	char	*str;

	(void)env;
	str = getcwd(NULL, 0);
	if (str == NULL)
		mini_error_one(18);
	else
	{
		ft_printf("%s\n", str);
		free(str);
	}
}
