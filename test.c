/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:55:51 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/20 10:04:31 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  <stdio.h>
#include  <unistd.h>
#include  <stdlib.h>
#include  <string.h>
#include  <readline/readline.h>
#include  <readline/history.h>

typedef enum s_type
{
    WORD,
    PIPE,
    red_in,
    red_out,
    heredoc,
    append,
}t_type;


typedef struct s_token
{
    char *value;
    t_type type;
    struct s_token *next;
}t_token;

typedef struct s_cmd
{
    char **args;
    char *infile;
    char *outfile;
    int append;
    struct s_cmd *next;
}t_cmd;

// void initialisation(t_cmd *cmd)
// {
//     cmd->append = NULL;
//     cmd->args =NULL;
//     cmd->infile = NULL;
//     cmd->outfile = NULL;
// }


/***************ARGS**********************/

//void add_to_args(char **args,char *word);
int count_word_in_tokens(t_token *token)
{
    int count = 0;
    while(token && token->type != PIPE)
    {
        if(token->type == WORD)
            count++;
        token = token->next;
    }
    printf(">count : %d<\n",count);
    return(count);
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

t_cmd *new_args(t_token *token)
{
    t_cmd *cmd;
    cmd = malloc(sizeof(t_cmd));
    if(!cmd)
        return NULL;
    // initialisation(cmd);
    int i =0;
    int nbr_args = count_word_in_tokens(token);
    cmd->args = malloc(sizeof(char *) * (nbr_args + 1));
    if(!cmd->args)
        return(free(cmd),NULL);
    while(token && token->type != PIPE)
    {
        if(token->type == WORD)
        {
            cmd->args[i] = ft_strdup(token->value);
            i++;
        }   
        else if(token->type == red_in)
            cmd->infile = ft_strdup(token->value);
        else if(token->type ==  red_out)
            cmd->outfile = ft_strdup(token->value);
        token = token->next;
    }
    cmd->args[i] = NULL;
    cmd->next = NULL; 
    return(cmd);
}

t_cmd  *add_cmd_back(t_cmd **lst,t_cmd  *new_cmd)
{
    t_cmd *tmp;
    if(!*lst)
        *lst = new_cmd;
    else
    {
        tmp = *lst;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = new_cmd;
        new_cmd->next = NULL;
    }
    return(new_cmd);
}
t_cmd *parse_toking(t_token *tokens)
{
    t_cmd *head = NULL;
    while(tokens)
    {
        t_cmd *cmd = new_args(tokens);
        add_cmd_back(&head,cmd);
        while(tokens && tokens->type != PIPE)
            tokens = tokens->next;
        if(tokens && tokens->type == PIPE)
            tokens = tokens->next;
    }
    return (head);
}

void print_cmd(t_cmd *command)
{
    int i = 0;
    while(command)
    {
        printf("-> %s\n",command->args[i++]);
        command = command->next;
    }
}

 /****************tokenize simple*************************/
int ft_isspace(int c)
{
    return((c == 32) || (c >= 9 && c <= 13));
}
t_token *create_token(char *value,t_type type)
{
    t_token *token;
    token = malloc(sizeof(t_token));
    if(!token)
        return NULL;
    token->value=strdup(value);
    token->type=-1;
    token->next=NULL;

    return (token);
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
            new = create_token(word,WORD);
            append_token(&head,new);
            if(input[i] == quote_char)
                i++;
        }
        
        else if(input[i] == '|')
        {
            new = create_token("|",PIPE);
            append_token(&head,new);
            i++;
        }
        else if(input[i] == '>')
        {
            new = create_token(">",red_out);
            append_token(&head,new);
            i++;
        }
        else if(input[i] == '<')
        {
            new = create_token("<",red_in);
            append_token(&head,new);
            i++;
        }
        else
        {
            start = i;
            while(input[i] && !ft_isspace(input[i]) && input[i] != '|' && input[i] != '>' && input[i] != '<')
                i++;
            word =substr(input,start,i - start);
            new = create_token(word,WORD);
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
        printf("->[%s]",token->value);
        printf(" -- [%d]\n",token->type);
        token = token->next;
    }
}

int main()
{
    char *input;
    t_token *res = NULL;
    t_cmd *parse = NULL;
    while(1)
    {
        input = readline("Minishell> ");
        if(!input)
           break;
        if(*input)
            add_history(input);
        res = tokenize(input);
        parse = parse_toking(res);
        print_tokens(res);
        printf("\n-----------\n");
        print_cmd(parse);
        // free(input);
    }
    free_token_list(res);
}