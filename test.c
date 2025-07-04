/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:55:51 by haboucha          #+#    #+#             */
/*   Updated: 2025/07/04 16:42:14 by haboucha         ###   ########.fr       */
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
    char quote_type;
    struct s_token *next;
}t_token;

typedef struct s_cmd
{
    char *cmd;
    char **args;
    char *infile;
    char *outfile;
    int append;
    struct s_cmd *next;
}t_cmd;

int ft_strlen(char *s)
{
    int i = 0;
    while(s[i])
        i++;
    return(i);
}

/*****************************UTILIS**************************************/
char	*ft_strdup(char *s1)
{
	char	*p;
	int		n;
	int		i;
    if(!s1)
        return NULL;
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

char *ft_strjoin(char *s1,char *s2)
{
    if(!s1 || !s2)
        return NULL;
    int i = 0;
    int j = 0;
    int len = ft_strlen(s1) + ft_strlen(s2);
    char *p = malloc(len + 1);
    if(!p)
        return NULL;
    while(s1[i])
    {
        p[j] = s1[i];
        i++;
        j++;
    }
    i=0;
    while(s2[i])
    {
        p[j] = s2[i];
        j++;
        i++;
    }
    p[j] = '\0';
    return (p);
}

int ft_isspace(int c)
{
    return((c == 32) || (c >= 9 && c <= 13));
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
/*****************************UTILIS*******************************/



/****************TOKINES SIMPLE*************************/
t_token *create_token(char *value,t_type type)
{
    t_token *token;
    token = malloc(sizeof(t_token));
    if(!token)
        return NULL;
    token->value=strdup(value);
    token->type =type;
    token->next=NULL;

    return (token);
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
            new->quote_type = quote_char;
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
/****************TOKINES SIMPLE*************************/

/****************TOKINES ARGS*************************/

//void add_to_args(char **args,char *word);
int count_word_in_tokens(t_token *token)
{
    int count = 0;
    int first_word = 0;
    while(token && token->type != PIPE)
    {
        if(token->type == WORD)
        {
            if(!first_word)
                first_word = 0;
            count++;
        }
    token = token->next;
    }
    return(count);
}

void initialisation(t_cmd *cmd)
{
    cmd->cmd = NULL;
    cmd->args =NULL;
    cmd->infile = NULL;
    cmd->append = 0;
    cmd->outfile = NULL;
}

t_cmd *new_args(t_token *token)
{
    t_cmd *cmd;
    cmd = malloc(sizeof(t_cmd));
    if(!cmd)
        return NULL;
    initialisation(cmd);
    int i =0;
    int nbr_args = count_word_in_tokens(token);
    cmd->args = malloc(sizeof(char *) * (nbr_args + 1));
    if(!cmd->args)
        return(free(cmd),NULL);
    while(token && token->type != PIPE)
    {
        if(token->type == WORD)
        {
            if(cmd->cmd == NULL)
            {
                cmd->cmd = ft_strdup(token->value);
                
            }
            else
                cmd->args[i++] = ft_strdup(token->value);
        }
        else if(token->type == red_out)
        {
            if(token->next)
                cmd->outfile = ft_strdup(token->next->value);
            token =token->next;
        }
        else if(token->type ==  red_in)
        {
            if(token->next)
                cmd->infile = ft_strdup(token->next->value);
            token =token->next;

        }
        token = token->next;
    }
    cmd->args[i]=NULL;
    return cmd;
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
/**************print cmd******************/
void print_cmd(t_cmd *command)
{
    int i = 0;
    while(command)
    {
        i = 0;
        printf("cmd: %s\n",command->cmd);
        while(command->args[i])
        {
            printf("args[%d]: %s\n",i,command->args[i]);
            i++;
        }
        printf("outfile:  %s\n",command->outfile);
        printf("infile: %s\n",command->infile);
        command = command->next;
    }
}
/****************TOKINES ARGS*************************/



/********************Expands*************************************/
int count_len(int num)
{
    int len = 0;
    if(num == 0)
        return 1;
    if(num < 0)
        len = 1;
    while(num != 0)
    {
        num/=10;
        len++;
    }
    return len;
}

char *itoa(int n)
{
    char *str;
    int i;
    int len;
    long j;

    j = n;
    len = count_len(n);
    str = malloc(len + 1);
    if(!str)
        return NULL;
    if(j < 0)
    {
        str[0] ='-';
        j*=-1;
    }
    i = len - 1;
    if(j == 0)
        str[0] ='0';
    while(j > 0)
    {
        str[i] = (j % 10) + '0';
        j = j / 10;
        i--;
    }
    str[len] = '\0';
    return(str);

}
 int ft_strncmp(char *s1,  char *s2, int n)
 {
    int i = 0;
    while(s1[i] && s2[i] && i < n)
    {
        if(s1[i] > s2[i])
            return 1;
        else if(s1[i] < s2[i])
            return -1;
        i++; 
    }
    if(i < n)
    {
         if(s1[i] > s2[i])
            return 1;
        else if(s1[i] < s2[i])
            return -1;
    }
    return 0;
 }

char *get_env_value(char *var,char **envp)
{
    int i = 0;
    int len = ft_strlen(var);
    while(envp[i])
    {
        if(ft_strncmp(envp[i],var,len) == 0 && envp[i][len] == '=')
            return (envp[i] + len + 1);
        i++;
    }
    return("");
}
int is_valid_env_char(char c)
{
    return((c >= 'A' && c <= 'Z')||(c >= 'a' && c <= 'z')||(c >= '0' && c <= '9') || c == '_');
}
char *ft_strjoin_char(char *s1,char c)
{
    int i = 0;
    int len = ft_strlen(s1) + 1;
    char *p = malloc(len + 1);
    if(!p)
        return NULL;
    while(s1[i])
    {
        p[i] = s1[i];
        i++;
    }
    p[i] = c;
    i++;
    p[i] ='\0';
    return p;
}
char *expand_string(char *word,char **envp)
{
    int i = 0;
    int start = 0;
    char *var_name;
    char *value;
    char *tmp;
    char quote = 0;
    char *result = ft_strdup("");
    if(!word)
        return (ft_strdup(""));
    while(word[i])
    {
            if(word[i] == '\'' && quote == 0)
            {
               quote = '\'';
                i++;
            }
            else if(word[i] == '\'' && quote == '\'')
            {
                quote = 0;
                i++;
            }
            else if(word[i] == '"' && quote == 0)
            {
                quote =  '"' ;
                i++;
            }
            else if(word[i] == '"' && quote ==  '"')
            {
                quote =0;
                i++;
            }
            else if(word[i] == '$' && quote != '\'')
            {
                i++;
                start = i;
                while(word[i] && is_valid_env_char(word[i]))
                    i++;
                var_name = substr(word,start,i - start);
                value = get_env_value(var_name,envp);
                free(var_name);

                tmp = ft_strjoin(result,value);
                free(result);
                result = tmp;
            }
            else
            {
                tmp = ft_strjoin_char(result,word[i]);
                free(result);
                result = tmp;
                i++;
            }
    }
    return (result);
}

void expand_token_list(t_token *head,char **envp)
{
    t_token *tmp = head;
    while(tmp)
    {
        if(tmp->type == WORD && tmp->value && tmp->quote_type != '\'')
        {
            char *expanded = expand_string(tmp->value,envp);
            free(tmp->value);
            tmp->value = expanded;
        }
        tmp = tmp->next;
    }
}
char *remove_quotes(char *input)
{
    char *result = malloc(ft_strlen(input) + 1);
    if(!result)
        return NULL;
    int i = 0;
    int j = 0;
    char quote  = 0;
    while(input[i])
    {
        if(quote == 0)
        {
            if(input[i] == '\'' || input[i] == '"')
            {
                quote = input[i];
                i++;
            }
            else
            {
                result[j] = input[i];
                j++;    
                i++;
            }
        }
        else
        {
            if(input[i] == quote)
            {
                quote = 0;
                i++;
            }
            else
            {
                result[j]=input[i];
                i++;
                j++;
            }
        }
    }
    result[j]='\0';
    return result;
}
void remove_quotes_from_tokens(t_token *tokens)
{
    while(tokens)
    {
        if(tokens->value)
        {
            char *tmp = tokens->value;
            tokens->value = remove_quotes(tokens->value);
            free(tmp);
        }
        tokens = tokens->next;
    }
}


int main(int argc,char **av,char **envp )
{
    char *input;
    t_token *res = NULL;
    t_cmd *parse = NULL;
    char *expand;
    while(1)
    {
        input = readline("Minishell> ");
        if(!input)
           break;
        if(*input)
            add_history(input);
        res = tokenize(input);
        expand_token_list(res,envp);
        // expand  = expand_string(input,envp);
        // free(expand);
        // print_tokens(res);
        // free(tmp);
        // remove_quotes_from_tokens(res);
        parse = parse_toking(res);
        print_cmd(parse);
        free(input);
    }
    free_token_list(res);
    return 0;
}
