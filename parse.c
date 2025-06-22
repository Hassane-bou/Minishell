/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:50:48 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/22 17:50:03 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void initilisation(t_cmd *cmd)
{
    cmd->cmd = NULL;
    cmd->args = NULL;
    cmd->infile =NULL;
    cmd->outfile = NULL;
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

void print_cmd(t_cmd *cmd)
{
    int i;
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
        printf("outfil: %s\n",cmd->outfile);
        printf("infile: %s\n",cmd->infile);
        printf("herdoc: %s\n",cmd->heredoc);
        cmd = cmd->next;
    }
}

t_cmd *add_back_cmd(t_cmd **cmd,t_cmd *new_cmd)
{

    if(!*cmd)
        *cmd = new_cmd;
    else
    {
        t_cmd *tmp = *cmd;
        while(tmp->next != NULL)
        {
            tmp= tmp->next;
        }
        tmp->next = new_cmd;
        new_cmd->next=NULL;
    }
    return(new_cmd);
}

t_cmd *new_cmd(t_token *token)
{
    t_cmd *cmd;
    cmd = malloc(sizeof(t_cmd));
    if(!cmd)
        return NULL;
    initilisation(cmd);
    int nbr_args = count_word_in_token(token);
    cmd->args = malloc(sizeof(char *) * (nbr_args + 1));
    if(!cmd->args)
        return(free(cmd),NULL);
    int i= 0;
    while(token && token->type != PIPE)
    {
        if(token->type == WORD)
        {
            if(cmd->cmd == NULL)
                cmd->cmd=ft_strdup(token->value);
            else
            {
                cmd->args[i] = ft_strdup(token->value);
                i++;
            }
        }
        else if(token->type == REDIR_OUT || token->type == APPEND)
        {
            if(token->type == APPEND)
                cmd->append =1;
            if(token->next)
                cmd->outfile = ft_strdup(token->next->value);
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
                cmd->heredoc = ft_strdup(token->next->value);
            token = token->next;
        }
        token = token->next;
    }
    cmd->args[i] = NULL;
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

