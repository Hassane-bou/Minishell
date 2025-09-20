/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 09:35:22 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/20 16:17:35 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum s_type
{
    append,
    heredoc,
    red_in,
    red_out,
    pipe,
    word,
}t_type;


typedef struct s_token
{
    char *value;
    t_type type;
    struct s_token *next;
}t_token;



int check_pipe_syntaxe(char *input)
{
    int i = 0;
    int len = strlen(input);
    int end_input = len - 1;
    int quote = 0;
    while(isspace(input[i]))
        i++;
    if(input[i] == '|')
        return(1);
    while(end_input >=0 && isspace(input[end_input]))
        end_input--;
    if(input[end_input] == '|')
        return 1;
    while(input[i])
    {
        if((input[i] == '\'' || input[i] =='"') && !quote)
            quote=input[i];
        else if(input[i] == quote)
            quote =0;
        if(!quote)
        {
            if(input[i] == '|' && input[i+1] && input[i+1] =='|')
                return 1;
            if(input[i] == '|')
            {
                int j = i + 1;
                while(isspace(input[j++]))
                    if(input[j] == '|')
                        return 1;
            }
        }
        i++;
    }
    return 0;
}

int check_redirection_syntaxe(char *input)
{
    int i = 0;
    char redirect;
    int count;
    while(input[i])
    {
        if(input[i] == '>' || input[i] == '<')
        {
            redirect=input[i];
            count = 0;
            while(input[i] == redirect)
            {
                count++;
                i++;
            }
            if(count > 2)
                return 1;
            while(isspace(input[i]))
                i++;
            if(input[i] =='\0' || input[i] == '>' || input[i] == '<' || input[i] =='|')
                return 1;
        }
        i++; 
    }
    return 0;
}
int check_quotes_syntaxe(char *input)
{
    int i = 0;
    char quote_char;

    while(input[i])
    {
        if((input[i] == '\'' || input[i] == '"') && !quote_char)
            quote_char = input[i];
        else if(input[i] == quote_char)
            quote_char =0;
        i++;
    }
    if(quote_char)
        return 1;
    else
        return 0;
}

int check_all_syntaxe(char *input)
{
    if(check_pipe_syntaxe(input))
    {
        printf("erreur pipe!!\n");
        return 1;
    }
    if(check_redirection_syntaxe(input))
    {
        printf("erreur redirection!!\n");
        return 1;
    }
    if(check_quotes_syntaxe(input))
    {
        printf("erreur quotes!!\n");
        return 1;
    }
    return 0;
}
char *ft_strdup(char *str)
{
    int i = 0;
    int len = strlen(str);
    char *p = malloc(len + 1);
    if(!p)
        return(NULL);
    while(str[i])
    {
        p[i] = str[i];
        i++;
    }
    p[i]='\0';
    return p;
    
}
t_token *create_token(char *value1,t_type type)
{
    t_token *new = malloc(sizeof(t_token));
    if(!new)
        return(NULL);
    new->value = ft_strdup(value1);
    new->type=type;
    new->next = NULL;

    return(new);
}

char *ft_substr(char *s, int start,int len)
{
    int i = 0;
    if(start > strlen(s))
        return(ft_strdup(""));
    if(start + len > strlen(s))
        len = strlen(s) - start;
    char *p = malloc(len + 1);
    if(!p)
        return(NULL);
    while(i < len)
    {
        p[i] = s[start + i];
        i++;
    }
    p[i] ='\0';
    return p;
}
void add_token(t_token **head,t_token *new)
{
    if(!*head)
        *head = new;
    else
    {
        t_token *tmp = *head;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}
void print_token(t_token *token)
{
    while(token)
    {
        printf("->[%s]\n",token->value);
        printf("->[%d]\n",token->type); 
        token =token->next;   
    }
}

t_token *tokenize(char *input)
{
    int i = 0;
    char *value;
    int start;
    t_token *new;
    t_token *head = NULL;
    while(input[i])
    {
        if(isspace(input[i]))
            i++;
        if(input[i]== '>' && input[i+1] == '>')
        {
            value = ft_substr(input,i,2);
            new = create_token(value,append);
            add_token(&head,new);
            free(value);       
            i+=2;
        }
        else if(input[i]== '<' && input[i+1] == '<')
        {
            value = ft_substr(input,i,2);
            new = create_token(value,heredoc);
            add_token(&head,new);
            free(value);       
            i+=2;
        }
        else if(input[i]== '<')
        {
            value = ft_substr(input,i,1);
            new = create_token(value,red_in);
            add_token(&head,new);
            free(value);       
            i++;
        }
        else if(input[i]== '>')
        {
            value = ft_substr(input,i,1);
            new = create_token(value,red_out);
            add_token(&head,new);
            free(value);       
            i++;
        } 
        else if(input[i]== '|')
        {
            value = ft_substr(input,i,1);
            new = create_token(value,pipe);
            add_token(&head,new);
            free(value);       
            i++;
        }
        else
        {
            start =i;
            while(input[i] && (input[i] != '|' && input[i] != '>' && input[i] != '<' && !isspace(input[i])))
                i++;
            value = ft_substr(input,start,i - start);
            new = create_token(value,word);
            add_token(&head,new);
            free(value);       
        }
    }
    return head;
}

int main(int argc,char **argv)
{
    if(argc != 1)
        return 1;
    (void)argv;
    char *input;
    t_token *res = NULL;
    while(1)
    {
        input = readline("Minishell> ");
        if(input == NULL)
            break;
        if(check_all_syntaxe(input))
            continue;
        res = tokenize(input);
        print_token(res);
    }
    return 0;

}