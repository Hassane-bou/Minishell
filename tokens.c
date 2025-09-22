/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:38:01 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/22 09:42:03 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*******************************Ceate tokens****************************/
t_token *cretae_token(char *value, t_type type)
{
    t_token *token = malloc(sizeof(t_token));
    if(!token)
        return NULL;
    token->value = ft_strdup(value);
    token->type = type;
    token->next = NULL;
    token->quoted = 0;
    return (token);
}

/***************************add_tokens_inliste******************************/
void append_token(t_token **head,t_token *new)
{
    if(!*head)
    {
        *head = new;
    }
    else
    {
        t_token *tmp = *head;
        while(tmp->next)
            tmp=tmp->next;
        tmp->next = new;
    }
}
/***********************handle word**************************/
int handle_word(char *input, int i, t_token **head)
{
    int start ;
    char *word;
    t_token *new;
    char q;
    start = i;
    q = 0;
    while (input[i] && (!ft_isspace(input[i]) && input[i] != '>' && input[i] != '<' && input[i] != '|'))
    {
        if (input[i] == '"' || input[i] == '\'')
        {
            char q = input[i++];
            while (input[i] && input[i] != q)
                i++;
            if (input[i] == q)
                i++;
        }
        else
            i++;
    }
    word = ft_substr(input,start,i - start);
    new = cretae_token(word,WORD);
    new->new_quote = q;
    append_token(head,new);
    free(word);
    return(i);
}

t_token *tokenize(char *input)
{
    int i = 0;
    t_token *head = NULL;
    while(input[i] != '\0')
    {
        if(ft_isspace(input[i]))
            i++;
        else if(input[i] == '>' && input[i + 1] =='>')
            i = handle_APPEND(input,i,&head);
        else if(input[i] == '<' && input[i + 1] == '<')
            i = handle_herdoc(input,i,&head);
        else if(input[i] == '>')
            i =  handle_outfile(input,i,&head);
        else if(input[i] == '<')
            i = handle_intfile(input,i,&head);
        else if(input[i] == '|')
            i = handle_pipe(input,i,&head);
        else
            i = handle_word(input,i,&head);
    }
    return (head);
}
