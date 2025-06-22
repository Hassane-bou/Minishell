/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:31:35 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/22 17:49:11 by haboucha         ###   ########.fr       */
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
        t_cmd *cmd;
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
            cmd = parse_cmd(result);
            // print_token(result);
            // printf("-------------------\n");
            print_cmd(cmd);
            free(input);
        }
}
