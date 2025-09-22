/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:30:31 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/22 10:16:50 by haboucha         ###   ########.fr       */
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
    int quoted;
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
    int error;
    t_redriection *red;
    struct s_cmd *next;
}t_cmd;

typedef struct s_expand
{
    char    *res;
    char    quote;
    int     i;
    int     g_exit_status;
    int     f;
    char    **envp;
}t_expand;


void signal_handler(int sig);
void handle_end(void);
void setup_signals(void);

/************check_syntaxe****************/
int check_quotes(char *input);
int check_pipe_syntaxe(char *input);
int check_pipe1_syntaxe(char *input,int i);
int check_redirection_syntaxe(char *input);
int	check_redirection1_syntaxe(char *input, int i);
int check_all_syntaxe(char *input);

/***************create tokens******************************/

t_token *cretae_token(char *value, t_type type);
void append_token(t_token **head,t_token *new);
int handle_APPEND(char *input,int i,t_token **head);
int handle_herdoc(char *input,int i,t_token **head);
int handle_outfile(char *input,int i,t_token **head);
int handle_intfile(char *input,int i,t_token **head);
int handle_pipe(char *input,int i,t_token **head);
int handle_word(char *input, int i, t_token **head);
t_token *tokenize(char *input);

/*********************parse tokens to cmc***************************************/

t_cmd	*new_cmd(t_token *token);
void	initilisation(t_cmd *cmd);
int	count_word_in_token(t_token *token);
void cmd_add(t_token *token,t_cmd *cmd);
void	add_red(t_type type, t_cmd *cmd, char *file);
t_redriection	*new_red(t_type type, char *file);
t_cmd	*add_back_cmd(t_cmd **cmd, t_cmd *new_cmd);
t_cmd *parse_cmd(t_token *token);
void print_cmd(t_cmd *cmd);


/******************expand_token_list**********************************************/

void expand_token_list(t_token **head,char **envp);
void expand_loop_list(t_token **head, t_expand *exp);
t_token	*expand_heredoc(t_token *tmp);
t_token	*expand_redirection(t_token *tmp, t_expand *e);
t_token	*expand_word(t_token *tmp, t_expand *e, t_token **head, t_token **prev);
char	*expand_string(char *word, t_expand *ex);
void	initialiser_vars(t_expand *e);
int	check_expand_quotes(char c, char *quote);
char	*expand_exit_status(char *res, int g_exit_status);
char	*expand_var_value(char *word, int *i, char *res, char **envp);
char	*append_char(char *res, char c);
int	has_quotes(char *s);
int	check_expand_quotes(char c, char *quote);
int	is_valid_env_char(char c);
char	*get_env_value(char *var, char **envp);
char	*ft_strjoin_char(char *s1, char c);
char	*remove_quotes(char *str);

/****************************utils_libft************************************/
char *ft_strjoin(char *s1,char *s2);
int ft_stncmp(char *s1,char *s2,int n);
int	count(int nbr);
char	*ft_itoa(int nbr);
int ft_isspace(int c);
char	*ft_strdup( char *s1);
char	*ft_substr(char *s, int start, int len);
int ft_strlen(char *s);

int	ft_count(char *str, char c);
char	**ft_split(char *str, char c);
char	*allocate_word(char **pr, int i, int j, int k);
char	*ft_strncpy(char *dst, char *src, int len);
void print_token(t_token *token);

#endif