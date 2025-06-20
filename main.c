/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:31:35 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/20 10:09:15 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_token(t_token *token)
{
    while(token)
    {
        printf("-> [%s]",token->value);
        printf("-- [%d]\n",token->type);
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
            if(check_all_syntaxe(input))
                continue;
            result = tokenize(input);
            print_token(result);
            free(input);
        }
}
