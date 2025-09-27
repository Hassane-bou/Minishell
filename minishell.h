/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:30:31 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/27 11:46:43 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/libft.h"
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>

extern int	g_signal;

# define RED "\033[1;31m"
# define RESET "\033[0m"
# define GREEN "\001\033[0;32m\002"

// ------------ parsing -----------------

typedef struct s_env
{
	char			*key;
	char			*value;
	int				status;
	int				exit_status;
	char			*prompt;
	struct s_env	*next;
}	t_env;

typedef enum e_type {
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
}	t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	char			new_quote;
	int				quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_redriection
{
	t_type					type;
	char					*file_or_delim;
	struct s_redriection	*next;
}	t_redriection;

typedef struct s_expand
{
	char	*res;
	char	quote;
	int		i;
	int		g_exit_status;
	int		f;
	char	**envp;
	t_token	*tmp;
}	t_expand;

typedef struct s_cmd
{
	int				quoted_del;
	char			*cmd;
	char			**args;
	t_redriection	*red;
	int				herdoc_fd;
	struct s_cmd	*next;
}	t_cmd;

void			signal_handler(int sig);
void			setup_signals(void);

/************check_syntaxe****************/
int				check_quotes(char *input);
int				check_pipe_syntaxe(char *input);
int				check_pipe1_syntaxe(char *input, int i);
int				check_redirection_syntaxe(char *input);
int				check_redirection1_syntaxe(char *input, int i);
int				check_all_syntaxe(char *input);

/***************create tokens******************************/

t_token			*create_token(char *value, t_type type);
void			append_token(t_token **head, t_token *new);
int				handle_append(char *input, int i, t_token **head);
int				handle_herdoc(char *input, int i, t_token **head);
int				handle_outfile(char *input, int i, t_token **head);
int				handle_intfile(char *input, int i, t_token **head);
int				handle_pipe(char *input, int i, t_token **head);
int				handle_word(char *input, int i, t_token **head);
t_token			*tokenize(char *input);

/*********************parse tokens to cmc************************/

t_cmd			*new_cmd(t_token *token);
void			initilisation(t_cmd *cmd);
int				count_word_in_token(t_token *token);
void			cmd_add(t_token *token, t_cmd *cmd);
void			add_red(t_type type, t_cmd *cmd, char *file);
t_redriection	*new_red(t_type type, char *file);
t_cmd			*add_back_cmd(t_cmd **cmd, t_cmd *new_cmd);
t_cmd			*parse_cmd(t_token *token);

/******************expand_token_list***************************/

void			expand_token_list(t_token **head, char **envp, t_env *env_head);
void			expand_loop_list(t_token **head,
					t_expand *exp, t_env *env_head);
t_token			*expand_heredoc(t_token *tmp, t_expand *e);
t_token			*expand_redirection(t_token *tmp, t_expand *e, t_env *env_head);
t_token			*expand_word(t_expand *e,
					t_token **head, t_token **prev, t_env *env_head);
char			*expand_string(char *word, t_expand *ex, t_env *env_head);
void			initialiser_vars(t_expand *e);
int				check_expand_quotes(char c, char *quote);
char			*expand_exit_status(char *res, int g_exit_status);
char			*expand_var_value(char *word, t_expand *ex);
char			*append_char(char *res, char c);
int				has_quotes(char *s);
int				check_expand_quotes(char c, char *quote);
int				is_valid_env_char(char c);
char			*get_env_value_par(char *var, char **envp);
char			*ft_strjoin_char(char *s1, char c);
char			*remove_quotes(char *str);
void			free_cmd_list(t_cmd *cmd);
int				ft_isspace(int c);
void			free_splited_token(char **word);
t_token			*remove_empty_token(t_expand *e,
					t_token **head, t_token **prev);
void			split_tokens(t_expand *e, char **words);
void			expand_helper(char *tmp,
					char *tmp2, t_expand *ex, char *var_name);

// -------------- execution ------------------

typedef struct s_help
{
	int		i;
	int		start;
	char	*key;
	char	*ptr_value;
	char	*value;
	char	*tmp;
	int		pos;
	int		status;
	int		prev_fd;
	int		pid;
	int		pipe_fd[2];
	char	*input;
	int		quoted;
	t_token	*temp;
}	t_help;

void			env_add_back(t_env **env_list, t_env *new_node);
void			env_copy(char **envp, t_env **env_head);
void			ft_update_shelvl(t_env *env_list);
int				ft_redirect_buil(t_cmd *cmd);
int				ft_env(t_env *env_copy);
int				ft_pwd(t_env *env_copy);
int				ft_cd(char *path, t_env **env_copy);
int				ft_strcmp(char *s1, char *s2);
int				ft_echo(char **arr, t_env *env_copy);
int				ft_unset(char **arr, t_env **env_copy);
int				ft_exit(char **arr, t_env **env_copy, t_cmd *cmd);
int				ft_export(char **arr, t_env **env_copy);
int				is_builtin(t_cmd *cmd);
char			*get_env_value(t_env **env_copy, char *key);
int				run_builtin(t_cmd *cmd, t_env **env_copy);
int				ft_execute(t_cmd *cmd, t_env **env_copy, char *input, int a);
char			**env_to_arr(t_env *env_head);
void			execute_multiple(t_cmd *cmd, t_env **env_copy);
void			child_process(t_cmd *cmd, char **env_arr, t_env **env_copy);
int				ft_herdoc(t_cmd *cmd, t_env **env_copy, int a);
void			cmd_built(t_cmd *cmd, t_env **env_copy, int *status);
void			setup_signals(void);
void			handle_end(t_env *env);
void			signal_handler(int sig);
void			setup_signals(void);
void			free_args(char **args);
void			ft_redirect(t_cmd *cmd);
void			free_env(t_env *head);
void			print_error(char *str);
void			key_value_alloc(t_help *var, char *str);
int				check_long(const char *str);
void			open_append(int *fd, t_redriection **tmp);
int				check_exp(char *str, t_env **env_copy);
void			print_export(t_env **env_copy);
char			*make_prompt(void);
void			print_tamazirt(void);
void			free_cmd_list(t_cmd *cmd);
void			free_args(char **args);
void			free_red_list(t_redriection *red);
void			free_cmd_list(t_cmd *cmd);
void			free_token_list(t_token *token);

# define ERROR_ARG "minishell: exit: too many arguments\n"

#endif