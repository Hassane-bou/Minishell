/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:39:46 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/22 12:36:16 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*******************HANDLE APPEND************************/
int handle_APPEND(char *input,int i,t_token **head)
{
    t_token *new_token;
    char *word;
    word = ft_substr(input,i,2);
    new_token = cretae_token(word,APPEND);
    append_token(head,new_token);
    free(word);
    i+=2;
    return i;
}
/*********************HANDLE HERDOC****************************/
int handle_herdoc(char *input,int i,t_token **head)
{
    char *word;
    t_token *new;
     word = ft_substr(input,i,2);
    new = cretae_token(word,HEREDOC);
    append_token(head,new);
    free(word);
    i+=2;
    return i;
}
/*************************HANDLE OUTFILE************************/
int handle_outfile(char *input,int i,t_token **head)
{
    char *word;
    t_token *new;
    word = ft_substr(input,i,1);
    new = cretae_token(word,REDIR_OUT);
    append_token(head,new);
    free(word);
    i++;
    return(i);
}
/*************************HANDLE INFILE************************/
int handle_intfile(char *input,int i,t_token **head)
{
    char *word;
    t_token *new;
    word = ft_substr(input,i,1);
    new = cretae_token(word,REDIR_IN);
    append_token(head,new);
    free(word);
    i++;
    return(i);
}
/*************************HANDLE PIPE************************/
int handle_pipe(char *input,int i,t_token **head)
{
    char *word;
    t_token *new;
    word = ft_substr(input,i,1);
    new = cretae_token(word,PIPE);
    append_token(head,new);
    free(word);
    i++;
    return(i);
}