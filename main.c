/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:31:35 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/10 13:28:18 by haboucha         ###   ########.fr       */
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

void free_token_list(t_token *token)
{
    t_token *tmp;
    while(token)
    {
        tmp = token;
        token = token->next;
        free(tmp->value);
        free(tmp);
    }
}

void free_red_list(t_redriection *red)
{
    t_redriection *tmp;
    while(red)
    {
        tmp = red;
        red = red->next;
        free(tmp->file_or_delim);
        free(tmp);
    }
    
}
void free_cmd_list(t_cmd *cmd)
{
    t_cmd *tmp;
    int i;
    while(cmd)
    {
        tmp = cmd;
        cmd = cmd->next;
        free(tmp->cmd);
        if(tmp->args)
        {
            i = 0;
            while(tmp->args[i])
            {
                free(tmp->args[i]);
                i++;
            }
            free(tmp->args);
        }
        if(tmp->red)
            free_red_list(tmp->red);
    free(tmp);
    }
}

void ff()
{
    system("leaks parse");
}

int main(int argc,char **argv,char **envp)
{
    if(argc != 1)
        return 1;
    atexit(ff);
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
        expand_token_list(&result,envp);
        cmd = parse_cmd(result);
    
        print_cmd(cmd);
        // free_red_list(cmd->red);
        free_cmd_list(cmd);
        free_token_list(result);
        free(input);
    }
    return 0;
}
