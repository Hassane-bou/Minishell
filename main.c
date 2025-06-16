/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:31:35 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/16 11:01:44 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_token(t_token *token)
{
    while(token)
    {
        printf("-> [%s]\n",token->value);
        token=token->next;
    }
}
int main()
{
  
        char *input;
        t_token *result;
        setup_signals();
        while(1)
        {
            input = readline("Minishell> ");
            if(input == NULL)
                handle_end();
            if(*input)
                add_history(input);
            if(check_quotes(input))
            {
                free(input);
                break;
            }
            if(check_pipe_syntaxe(input))
            {
                printf("erreur pipe\n");
                free(input);
                break;
            }
            if(check_redirection_syntaxe(input))
            {
                printf("erreur redirection\n");
                free(input);
                break;
            }
            result = tokenize(input);
            print_token(result);
            free(input);
        }
}