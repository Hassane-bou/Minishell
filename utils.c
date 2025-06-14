/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:13:14 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/14 09:49:12 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_isspace(int c)
{
    return(c == 32  || (c >= 9 && c <= 13));
}

void signal_handler(int sig)
{
    (void)sig;
    write(1,"\n",1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
void handle_end(void)
{
    write(1,"exit\n",5);
    exit(0);
}
void setup_signals(void)
{
    signal(SIGINT, signal_handler);
    signal(SIGQUIT,SIG_IGN);
}