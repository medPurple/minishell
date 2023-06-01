/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:49:08 by ml                #+#    #+#             */
/*   Updated: 2023/06/01 09:20:40 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    signal_ctrlc(int sig) // reagit au ctrl c afin de generer une nvl ligne ds sortie erreur, efface ligne en cours et rafraichit terminal
{
    (void)sig;
    write(2, "\n", 1);
    rl_replace_line("", 0); // remplace ligne actuelle avec une chaine vide.
    rl_on_new_line();// deplace curseur a une nouvelle ligne
    rl_redisplay(); // met a jour l affichage du terminal
}