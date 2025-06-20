/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:38:01 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/20 11:42:27 by haboucha         ###   ########.fr       */
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
/****************check syntaxe quotes*****************/
int check_quotes(char *input)
{
    int i = 0;
    char quote_char = 0;
    while(input[i])
    {
        if((input[i] == '\'' || input[i] == '"') && !quote_char)
            quote_char = input[i];
        else if(input[i] == quote_char)
            quote_char = 0;
        i++;
    }
    if(quote_char)
        return (1);
    else 
        return 0;
}
/****************check syntaxe pipe*****************/
int check_pipe_syntaxe(char *input)
{
    int i =0;
    int len = ft_strlen(input) ;
    int end_input = len - 1;
    char quote = 0;
    while(ft_isspace(input[i]))
        i++;
    if(input[i] == '|')
        return 1;
    while(end_input >= 0 && ft_isspace(input[end_input]))
        end_input--;
    if(input[end_input] == '|')
        return 1;
    while(input[i])
    {
         if ((input[i] == '\'' || input[i] == '"') && !quote)
            quote = input[i];
        else if (input[i] == quote)
            quote = 0;
        if(!quote)
        {
            if(input[i] == '|' && input[i+1] && input[i+1]=='|')
                return 1;
            if(input[i] == '|')
            {
                int j = i + 1;
                while (ft_isspace(input[j]))
                    j++;
                if(input[j] == '|')
                    return 1;  
            }
        }
        i++;    
    }
    return 0;
}

/****************check syntaxe redirection*****************/
int check_redirection_syntaxe(char *input)
{
    int i = 0;
    char redirect;
    int count;
    char quote = 0;
    while(input[i])
    {
        if ((input[i] == '"' || input[i] == '\'') && !quote)
        {
            quote = input[i];
            i++;
            while (input[i] && input[i] != quote)
                i++;
            if (input[i] == quote)
                quote = 0;
            i++;
            continue;
        }
        if(input[i]== '>' || input[i] == '<')
        {
            redirect = input[i];
            count = 0;
            while(input[i] == redirect)
            {
                count++;
                i++;
            }
            if(count > 2)
                return 1;
            while(ft_isspace(input[i]))
                i++;
            if(input[i] == '\0' || input[i] == '|' || input[i] == '>' || input[i] == '<')
                return 1;
        }
        else
            i++;   
        }
   return 0;
}
/********************check all syntaxe**************/
int check_all_syntaxe(char *input)
{
    if(check_pipe_syntaxe(input))
    {
        printf("erreur pipe\n");
        return 1;
    }
    if(check_quotes(input))
    {
        printf("erreur quotes\n");
        return 1;
    }
    if(check_redirection_syntaxe(input))
    {
        printf("erreur redirection\n");
        return 1;
    }
    return 0;
}



/****************HANDLE QUtes****************/
// int handle_quotes(char *input,int i,t_token **head)
// {
//     char quote_char;
//     int start;
//     t_token *new_token = NULL;
//     char *word;

//     quote_char=input[i];
//     i++;
//     start = i;
//     while(input[i] && input[i] != quote_char)
//         i++;
//     word = ft_substr(input,start,i - start);
//     new_token = cretae_token(word,WORD);
//     append_token(head,new_token);
//     if(input[i] == quote_char)
//         i++;
//     return i;
// }
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
/***********************handle word**************************/
int handle_word(char *input, int i, t_token **head)
{
    int start ;
    char *word;
    t_token *new;
    char quotes;
    start = i;
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
    append_token(head,new);
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
        // else if(input[i]=='"' || input[i] == '\'')
        //     i = handle_quotes(input,i,&head);
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
