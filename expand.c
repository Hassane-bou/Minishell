/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:58:54 by haboucha          #+#    #+#             */
/*   Updated: 2025/07/05 19:25:40 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_env_char(char c)
{
    return((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_');
}
int ft_stncmp(char *s1,char *s2,int n)
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
        if(ft_stncmp(envp[i],var,len) == 0 && envp[i][len] == '=')
            return(envp[i] + len + 1);
        i++;  
    }
    return("");
}
char *ft_strjoin(char *s1,char *s2)
{
    int i = 0;
    int j = 0;
    int len = ft_strlen(s1) + ft_strlen(s2);
    char *p = malloc(len + 1);
    if(!p)
        return NULL;
    while(s1[i])
    {
        p[j] =s1[i];
        i++;
        j++;
    }
    i = 0;
    while(s2[i])
    {
        p[j] = s2[i];
        i++;
        j++;
    }
    p[j]= '\0';
    return(p);
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
    int i =0;
    int start = 0;
    char *var_name;
    char *value;
    char *tmp;
    char quote = 0;
    char *resulat = ft_strdup("");
    if(!word)
        return(ft_strdup(""));
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
            quote = '"';
            i++;
        }
        else if(word[i] == '"' && quote == '"')
        {
            quote = 0;
            i++;
        }
        else if(word[i] == '$' && quote !='\'' )
        {
            i++;
            start = i;
            while(word[i] && is_valid_env_char(word[i]))
                i++;
            var_name = ft_substr(word,start,i -start);
            value = get_env_value(var_name,envp);
            free(var_name);

            tmp = ft_strjoin(resulat,value);
            free(resulat);
            resulat = tmp;
        }
        else
        {
            tmp = ft_strjoin_char(resulat,word[i]);
            free(resulat);
            resulat =tmp;
            i++;
        }
    }
    return(resulat);
}

int herdoc_quoted(t_token *token)
{
    if(!token || !token->value || token->type != HEREDOC)
        return 0;
    int len = ft_strlen(token->value);
    if(token->value[0] == '\'' || token->value[0] == '"' || token->value[len - 1] == '\''
        || token->value[len -1] == '"')
        return 1;
    return 0;
}

void expand_token_list(t_token *head,char **envp)
{
    t_token *tmp = head;
    while(tmp)
    {
        if(tmp->type == WORD && tmp->value && tmp->new_quote != '\'')
        {
            char *expanded = expand_string(tmp->value,envp);
            free(tmp->value);
            tmp->value = expanded;
        }
        tmp = tmp->next;
    }
}