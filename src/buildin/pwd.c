/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:16:00 by wmessmer          #+#    #+#             */
/*   Updated: 2023/06/22 14:56:55 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mini_pwd(t_env *env)
{
	char	*str;

	(void)env;
	str = getcwd(NULL, 0);
	ft_printf("%s\n", str);
	free(str);
}
