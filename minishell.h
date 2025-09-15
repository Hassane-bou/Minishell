/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:30:31 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/15 11:22:21 by haboucha         ###   ########.fr       */
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

extern int g_exit_status;

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
    char new_quote;
    struct s_token *next;
}t_token;



// typedef struct s_heredoc
// {
//     char *delimiter;
//     int quoted;
// } t_heredoc;

typedef struct s_redriection
{
    t_type type;
    char *file_or_delim;
    struct s_redriection *next;
}t_redriection;

typedef struct s_cmd
{
    char *cmd;
    char **args;
    t_redriection *red;

    struct s_cmd *next;
}t_cmd;





void signal_handler(int sig);
void handle_end(void);
void setup_signals(void);

/************check_syntaxe****************/
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




void expand_token_list(t_token **head,char **envp);
char *expand_string(char *word,char **envp,int *f);
char *ft_strjoin(char *s1,char *s2);
char *get_env_value(char *var,char **envp);
int ft_stncmp(char *s1,char *s2,int n);
int is_valid_env_char(char c);
int count(int nbr);



int	ft_count(char *str, char c);
char	**ft_split(char *str, char c);
char	*allocate_word(char **pr, int i, int j, int k);
char	*ft_strncpy(char *dst, char *src, int len);
#endif