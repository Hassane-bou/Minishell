/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:31:35 by haboucha          #+#    #+#             */
/*   Updated: 2025/07/05 18:27:55 by haboucha         ###   ########.fr       */
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
int main(int argc,char **argv,char **envp)
{
    if(argc != 1)
        return 1;
    (void)argv;
    char *input;
    t_token *result = NULL;
    t_cmd *cmd = NULL;
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
        // print_token(result);
        expand_token_list(result,envp);
        cmd = parse_cmd(result);
        print_cmd(cmd);       
        free(input);
    }
    return 0;
}
