/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:30:31 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/16 11:01:04 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef enum e_type {
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC,
}t_type;

typedef struct s_token
{
    char *value;
    t_type type;
    struct s_token *next;
}t_token;


typedef struct s_list
{
    char *text;
    struct s_list *next;
}t_list;


void handle_end(void);
void setup_signals(void);
char	**ft_split(char *str, char c);
char	*allocate_word(char **pr, int i, int j, int k);
char	*ft_strncpy(char *dst, char *src, int len);
int	ft_count(char *str, char c);
t_token *tokenize(char *input);
int ft_isspace(int c);
char	*ft_strdup( char *s1);
char	*ft_substr(char *s, int start, int len);
int ft_strlen(char *s);
int check_quotes(char *input);
int check_pipe_syntaxe(char *input);
int check_redirection_syntaxe(char *input);
#endif