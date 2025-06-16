/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:55:51 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/16 10:16:20 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  <stdio.h>
#include  <unistd.h>
#include  <stdlib.h>
#include  <string.h>
#include  <readline/readline.h>
#include  <readline/history.h>


typedef struct s_token
{
    char *value;
    struct s_token *next;
}t_token;

int ft_isspace(int c)
{
    return((c == 32) || (c >= 9 && c <= 13));
}
t_token *create_token(char *value)
{
    t_token *token;
    token = malloc(sizeof(t_token));
    if(!token)
        return NULL;
    token->value=strdup(value);
    token->next=NULL;

    return (token);
}
int ft_strlen(char *s)
{
    int i = 0;
    while(s[i])
        i++;
    return(i);
}
char	*ft_strdup(char *s1)
{
	char	*p;
	int		n;
	int		i;

	p = (char *)s1;
	n = ft_strlen(s1) + 1;
	i = 0;
	p = (char *)malloc(n * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (s1[i])
	{
		p[i] = (char)s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
char *substr(char *s,unsigned int start, size_t len)
{
    char *p;
    size_t i;

    if(!s)
        return NULL;
    if(start >= ft_strlen(s))
        return(ft_strdup(""));
    if(start + len > ft_strlen(s))
        len = ft_strlen(s) - start;
    p = malloc((len + 1) * sizeof(char));
    if(!p)
        return(NULL);
    i = 0;
    while(i < len)
    {
        p[i] = s[start + i];
        i++;
    }
    p[i]='\0';
    return p;
        
}

void append_token(t_token **head, t_token *new)
{
    if(!*head)
    {
        *head = new;
    }
    else
    {
        t_token *tmp = *head;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next=new;
    }
}

t_token *tokenize(char *input)
{
    t_token *head = NULL;
    t_token *new;
    char *word;
    char quote_char;
    int start = 0;
    int i = 0;
    while(input[i] != '\0')
    {
        if(ft_isspace(input[i]))
            i++;
        else if(input[i] == '"' || input[i]== '\'')
        {
            quote_char = input[i];
            i++;
            start = i;
            while(input[i] && input[i] != quote_char)
                i++;
            word =substr(input,start,i - start);
            new = create_token(word);
            append_token(&head,new);
            if(input[i] == quote_char)
                i++;
        }
        
        else if(input[i] == '|')
        {
            new = create_token("|");
            append_token(&head,new);
            i++;
        }
        else if(input[i] == '>')
        {
            new = create_token(">");
            append_token(&head,new);
            i++;
        }
        else if(input[i] == '<')
        {
            new = create_token("<");
            append_token(&head,new);
            i++;
        }
        else
        {
            start = i;
            while(input[i] && !ft_isspace(input[i]) && input[i] != '|' && input[i] != '>' && input[i] != '<')
                i++;
            word =substr(input,start,i - start);
            new = create_token(word);
            append_token(&head,new);
        }
    }
    return (head);
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
 
void print_tokens(t_token *token)
{
    while(token)
    {
        printf("->[%s]\n",token->value);
        token = token->next;
    }
}

int main()
{
    char *input;
    t_token *res = NULL;
    while(1)
    {
        input = readline("Minishell> ");
        if(!input)
           break;
        if(*input)
            add_history(input);
        res = tokenize(input);
        print_tokens(res);
        free(input);
    }
    free_token_list(res);
}