/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:38:01 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/14 13:10:35 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_token *cretae_token(char *value, t_type type)
{
    t_token *token = malloc(sizeof(t_token));
    if(!token)
        return NULL;
    token->value = ft_strdup(value);
    token->type = type;
    token->next = NULL;

    return (token);
}
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


t_token *tokenize(char *input)
{
    int i = 0;
    t_token *new = NULL;
    t_token *head = NULL;
    char *word;
    int start = 0;
    char quote_char;

    while(input[i] != '\0')
    {
        if(ft_isspace(input[i]))
            i++;
        else if(input[i]=='"' || input[i] == '\'')
        {
            quote_char=input[i];
            i++;
            start = i;
            while(input[i] && input[i] != quote_char)
                i++;
            word = ft_substr(input,start,i - start);
            new = cretae_token(word,WORD);
            append_token(&head,new);
            if(input[i] == quote_char)
                i++;
        }
        else if(input[i] == '>' && input[i + 1] =='>')
        {
            word = ft_substr(input,i,2);
            new = cretae_token(word,APPEND);
            append_token(&head,new);
            free(word);
            i+=2;
        }
        else if(input[i] == '<' && input[i + 1] == '<')
        {
            word = ft_substr(input,i,2);
            new = cretae_token(word,HEREDOC);
            append_token(&head,new);
            free(word);
            i+=2;
        }
        else if(input[i] == '>')
        {
            word = ft_substr(input,i,1);
            new = cretae_token(word,REDIR_OUT);
            append_token(&head,new);
            free(word);
            i++;
        }
        else if(input[i] == '<')
        {
            word = ft_substr(input,i,1);
            new = cretae_token(word,REDIR_IN);
            append_token(&head,new);
            free(word);
            i++;
        }
        else if(input[i] == '|')
        {
            word = ft_substr(input,i,1);
            new = cretae_token(word,PIPE);
            append_token(&head,new);
            free(word);
            i++;
        }
        else 
        {
            start = i;
            while(input[i] && (!ft_isspace(input[i]) && input[i] != '>' && input[i] != '<' && input[i] != '|'))
                i++;
            word = ft_substr(input,start,i - start);
            new = cretae_token(word,WORD);
            append_token(&head,new);
        }
    }
    return (head);
}
