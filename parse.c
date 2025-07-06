/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:50:48 by haboucha          #+#    #+#             */
/*   Updated: 2025/07/06 11:54:36 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void initilisation(t_cmd *cmd)
{
    cmd->cmd = NULL;
    cmd->args = NULL;
    cmd->infile =NULL;
    cmd->outfile = NULL;
    cmd->heredoc = NULL;
    cmd->append = 0;
}

int count_word_in_token(t_token *token)
{
    int count = 0;
    while(token && token->type != PIPE)
    {
        if(token->type == WORD)
        {
            count++;
        }
        token = token->next;
    }
    return(count);  
}
int count_redirect_in_token(t_token *token)
{
    int count = 0;
    while(token && token->type != PIPE)
    {
        if(token->type == REDIR_OUT)
            count++;
        token = token->next;
    }
    return (count);
}


void print_cmd(t_cmd *cmd)
{
    int i;
    // int j;
    while(cmd)
    {
        i = 0;
        printf("cmd: %s\n",cmd->cmd);
        if(cmd->args)
        {
            while(cmd->args[i])
            {
                printf("args[%d]: %s\n",i,cmd->args[i]);
                i++;
                
            }
        }
        int j = 0;
        if(cmd->outfile)
        {
            while(cmd->outfile[j])
            {
                printf("outfil[%d]: %s\n",j,cmd->outfile[j]);
                j++;

            }
        }
        int k = 0;
        if(cmd->heredoc)
        {
            while(cmd->heredoc[k].delimiter)
            {
                printf("herdoc[%d]: %s\n",k,cmd->heredoc[k].delimiter);
                k++;
            }
        }
        printf("infile: %s\n",cmd->infile);
        cmd = cmd->next;
    }
}

t_cmd *add_back_cmd(t_cmd **cmd,t_cmd *new_cmd)
{
    t_cmd *tmp;
    if(!cmd || !new_cmd)
        return NULL;
    if(!*cmd)
        *cmd = new_cmd;
    else
    {
        tmp = *cmd;
        while(tmp->next)
            tmp= tmp->next;
        tmp->next = new_cmd;

    }
    return(new_cmd);
}
int count_pipe(t_token *token)
{
    int i = 0;
    while(token)
    {
        if(token->type == PIPE)
            i++;
        token = token->next;
    }
    return i;
}

char *remove_quotes(char *str)
{
    int i = 0;
    int j  =0;
    int len = ft_strlen(str);
    char *res = malloc(len +1);
    if(!res)
        return NULL;
    while(str[i])
    {
        if(str[i] != '\'' && str[i] != '"')
            res[j++] = str[i];
        i++;
    }
    res[j] = '\0';
    return res;
}

t_cmd *new_cmd(t_token *token)
{
    t_cmd *cmd;
    cmd = malloc(sizeof(t_cmd));
    if(!cmd)
        return NULL;
    initilisation(cmd);
    int nbr_args = count_word_in_token(token);
    int nbr_red = count_redirect_in_token(token);
    cmd->args = malloc(sizeof(char *) * (nbr_args + 2));
    if(!cmd->args)
        return(free(cmd),NULL);
    cmd->outfile = malloc(sizeof(char *) * (nbr_red + 1));
    if(!cmd->outfile)
        return(free(cmd),free(cmd->args),NULL);
    cmd->heredoc = malloc(sizeof(t_heredoc) * (nbr_red + 1));
    if(!cmd->outfile)
        return(free(cmd),free(cmd->args),NULL);
    int j= 0;
    int i= 0;
    int h= 0;
    while(token && token->type != PIPE)
    {
        if(token->type == WORD)
        {
            if(cmd->cmd == NULL)
            {
                cmd->cmd=ft_strdup(token->value);
                cmd->args[0] = ft_strdup(token->value);
                i = 1;
            }
            else
            {
                cmd->args[i] = ft_strdup(token->value);
                i++;
            }
        }
        else if(token->type == REDIR_OUT || token->type == APPEND)
        {
            
            if(token->type == APPEND)
                cmd->append = 1;
            if(token->next)
            {
                cmd->outfile[j] =  ft_strdup(token->next->value);
                j++;
            }
            token = token->next;
        }
        else if(token->type == REDIR_IN)
        {
            if(token->next)
                cmd->infile = ft_strdup(token->next->value);
            token = token->next;
        }
        else if(token->type == HEREDOC)
        {
            if(token->next)
            {
                char *clean_delim = remove_quotes(token->next->value);
                cmd->heredoc[h].delimiter = clean_delim;
                cmd->heredoc[h].quoted = (token->next->new_quote != 0);
                h++;
            }
            token = token->next;
        }
        token = token->next;
    }
    cmd->heredoc[h].delimiter = NULL;
    cmd->outfile[j]=NULL;
    cmd->args[i] = NULL;
    cmd->next =NULL;
    return(cmd);
}
t_cmd *parse_cmd(t_token *token)
{
    t_cmd *head = NULL;
    t_cmd *cmd;
    
    while(token)
    {
        cmd = new_cmd(token);
        add_back_cmd(&head,cmd);
        while(token && token->type != PIPE)
            token = token->next;
        if(token && token->type == PIPE)
            token = token->next;
    }
    return(head);
}

