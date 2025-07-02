/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:30:31 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/30 10:05:43 by haboucha         ###   ########.fr       */
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



typedef struct s_cmd
{
    int pipecount;
    char *cmd;
    char **args;
    char **outfile;
    char *infile;
    int append;
    char *heredoc;
    struct s_cmd *next;
}t_cmd;






void signal_handler(int sig);
void handle_end(void);
void setup_signals(void);

int check_quotes(char *input);
int check_pipe_syntaxe(char *input);
int check_redirection_syntaxe(char *input);
int check_all_syntaxe(char *input);

t_token *cretae_token(char *value, t_type type);
void append_token(t_token **head,t_token *new);
int handle_APPEND(char *input,int i,t_token **head);
int handle_herdoc(char *input,int i,t_token **head);
int handle_outfile(char *input,int i,t_token **head);
int handle_intfile(char *input,int i,t_token **head);
int handle_pipe(char *input,int i,t_token **head);
int handle_word(char *input, int i, t_token **head);
t_token *tokenize(char *input);
t_cmd *parse_cmd(t_token *token);
void print_cmd(t_cmd *cmd);


int ft_isspace(int c);
char	*ft_strdup( char *s1);
char	*ft_substr(char *s, int start, int len);
int ft_strlen(char *s);



int	ft_count(char *str, char c);
char	**ft_split(char *str, char c);
char	*allocate_word(char **pr, int i, int j, int k);
char	*ft_strncpy(char *dst, char *src, int len);
#endif