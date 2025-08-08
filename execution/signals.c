/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:37:38 by rmouafik          #+#    #+#             */
/*   Updated: 2025/07/09 11:34:03 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void signal_handler(int sig)
{
    (void)sig;
    write(1,"\n",1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void disable_echoctl(void)
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void handle_end(void)
{
    write(1,"exit\n",5);
    exit(0);
}
void setup_signals(void)
{
    disable_echoctl();
    signal(SIGINT, signal_handler);
    signal(SIGQUIT,SIG_IGN);
}
