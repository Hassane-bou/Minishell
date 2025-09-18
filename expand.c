/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:58:54 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/18 10:18:22 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
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
    return(NULL);
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
int count(int nbr)
{
    int count = 0;
    if(nbr == 0)
        return(1); 
    else if(nbr < 0)
    {
        nbr *=-1;
        count++;
    }
    while(nbr > 0)
    {
        nbr = nbr / 10;
        count++;
    }
    return(count);
}

char *ft_itoa(int nbr)
{
    int i;
    int len =count(nbr);

    i = len -1;
    char *p =malloc(len + 1);
    if(!p)
        return(NULL);
    if(nbr == 0)
    {
        p[0] ='0';
        p[1] ='\0';
        return(p);
    }
    if(nbr < 0)
    {
        p[0] = '-';
        nbr *= -1;
    }
    while(nbr > 0)
    {
        p[i] = (nbr % 10) + '0';
        nbr = nbr /10;
    i--;
    }
    p[len] ='\0';
    return(p);
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

char *expand_string(char *word,char **envp, int *f)
{
    int i =0;
    int start = 0;
    int g_exit_status = 0;
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
            (*f)=1;
            i++;
            if(word[i] == '?')
            {
                char *str = ft_itoa(g_exit_status);
                tmp = ft_strjoin(resulat,str);
                free(resulat);
                free(str);
                resulat = tmp;
                i++;
            }
            start = i;
            while(word[i] && is_valid_env_char(word[i]))
                i++;
            var_name = ft_substr(word,start,i -start);
            value = get_env_value(var_name,envp);
            // update ici pour redirction in out append
            if(value == NULL)
            {
                tmp = ft_strjoin(resulat,word);
                free(resulat);
                resulat = tmp;
            }
            if(value)
            {
                tmp = ft_strjoin(resulat,value);
                free(resulat);
                resulat = tmp;
            }
            free(var_name);
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

t_token *export_value(char *export)
{
    t_token *new_token;
    t_token *head;
    t_token *tmp;
    
    char **value;
    int i = 0;
    
    // free double array value 
    value =ft_split(export,' ');
    if(!value)
        return NULL;
        
    tmp = cretae_token(value[i],WORD);
    if(!tmp)
        return(free(value),NULL);
    head = tmp;
    i++;
    while(value[i])
    {
        new_token = malloc(sizeof(t_token));
        if(!new_token)
            return(free(value),NULL);
        new_token->value = ft_strdup(value[i]);
        new_token->type = WORD;
        new_token->new_quote = 0;
        new_token->next = NULL;
        tmp->next = new_token;
        tmp=tmp->next;
        i++;
    }
    return(head);
}
int    has_quotes(char *s)
{
    int    i;

    if (!s)
        return (1); // if NULL, treat as no quotes -> expand
    i = 0;
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '"')
            return (0); // found quotes -> do NOT expand
        i++;
    }
    return (1); // no quotes -> expand
}
void expand_token_list(t_token **head,char **envp)
{
    t_token *tmp = *head;
    t_token *prev = NULL;
    t_token *res;
    int f;
    
    while(tmp)
    {
        f=0;
        if (tmp->type == HEREDOC && tmp->next)
        {
            if(!has_quotes(tmp->next->value))
                tmp->quoted = 1;
            tmp->next->value = remove_quotes(tmp->next->value);
            tmp = tmp->next->next;
            continue;
        }
        
        if(tmp->type == WORD && tmp->value && tmp->new_quote != '\'')
        {
            char *expanded = expand_string(tmp->value,envp, &f);
            free(tmp->value);
            tmp->value = expanded;
            // split export and toknes
            int i = 0;
            while(tmp->value[i])
            {
                if(isspace(tmp->value[i]))
                {
                    res = export_value(expanded);
                    if(prev)
                        prev->next = res;
                    else
                        *head = res;
                    t_token *last = res;
                    while(last->next)
                        last = last->next;
                    last->next = tmp->next;
                    free(tmp->value);
                    free(tmp);
                    tmp =last;
                }
                i++;
            }
            if(tmp->value[0] == '\0' && f==1)
            {
                t_token *to_free =tmp;
                if(prev)
                    prev->next = tmp->next;
                else
                    *head =tmp->next;
                tmp = tmp->next;
                free(to_free->value);
                free(to_free);
                continue;
            }
        }
        prev=tmp;
        tmp = tmp->next;
    }
    print_token(*head);
}

