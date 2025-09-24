/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:35:46 by rmouafik          #+#    #+#             */
/*   Updated: 2025/09/24 10:47:07 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return (1);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	is_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "env") || !ft_strcmp(cmd->args[0], "ENV"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "pwd") || !ft_strcmp(cmd->args[0], "PWD"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "echo") || !ft_strcmp(cmd->args[0], "ECHO"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "export"))
		return (1);
	return (0);
}

int	run_builtin(t_cmd *cmd, t_env **env_copy)
{
	if (!ft_strcmp(cmd->args[0], "env") || !ft_strcmp(cmd->args[0], "ENV"))
		return (ft_env(*env_copy));
	if (!ft_strcmp(cmd->args[0], "pwd") || !ft_strcmp(cmd->args[0], "PWD"))
		return (ft_pwd(*env_copy));
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(cmd->args[1], env_copy));
	if (!ft_strcmp(cmd->args[0], "echo") || !ft_strcmp(cmd->args[0], "ECHO"))
		return (ft_echo(cmd->args, *env_copy));
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(cmd->args, env_copy));
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(cmd->args, env_copy, cmd));
	if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(cmd->args, env_copy));
	return (1);
}

char	**env_to_arr(t_env *env_head)
{
	char	**env_arr;
	t_env	*tmp;
	char	*temp;
	int (i), (size);

	i = 0;
	size = 0;
	tmp = env_head;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	env_arr = malloc(sizeof(char *) * (size + 1));
	if (!env_arr)
		return (NULL);
	while (env_head)
	{
		temp = ft_strjoin(env_head->key, "=");
		env_arr[i] = ft_strjoin(temp, env_head->value);
		free(temp);
		i++;
		env_head = env_head->next;
	}
	return (env_arr[i] = NULL, env_arr);
}

void	print_tamazirt(void)
{
	printf(GREEN
		"\n"
		" ███    ███ ██╗███╗   ██╗██╗███████╗██╗  ██╗ ███████╗██╗     ██╗     \n"
		" ████  ████ ██║████╗  ██║██║██╔════╝██║  ██║ ██╔════╝██║     ██║     \n"
		" ██╔████╔██ ██║██╔██╗ ██║██║███████╗███████║ █████╗  ██║     ██║     \n"
		" ██║╚██╔╝██ ██║██║╚██╗██║██║╚════██║██╔══██║ ██╔══╝  ██║     ██║     \n"
		" ██║ ╚═╝ ██ ██║██║ ╚████║██║███████║██║  ██║ ███████╗███████╗███████╗\n"
		" ╚═╝     ╚═ ╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝ ╚══════╝╚══════╝╚══════╝\n"
		"Tamazirt shell 😎 — ready to cook some Amlou\n"
		RESET "\n");
}

char *make_prompt(void)
{
    char *pwd = getcwd(NULL, 0);
    char *suffix = ft_strjoin(pwd, "$> ");
    char *colored = ft_strjoin("\033[1;32m", suffix);
    char *final_prompt = ft_strjoin(colored, "\001\033[0m\002");
    free(pwd);
    free(suffix);
    free(colored);
    return final_prompt;
}

int check_synstax(char *input, t_env *head)
{
	if (check_all_syntaxe(input) == 1)
	{
		head->exit_status = 258;
		return 1;
	}
	else
		return 0;
}

void	free_args(char **args)
{
	int i = 0;

	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
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

void free_red_list(t_redriection *red)
{
    t_redriection *tmp;

    while(red)
    {
        tmp = red;
        red = red->next;
        free(tmp->file_or_delim);
        free(tmp);
    }
}

void free_cmd_list(t_cmd *cmd)
{
    t_cmd *tmp;
    int i;
    while(cmd)
    {
        tmp = cmd;
        cmd = cmd->next;
        free(tmp->cmd);
        if(tmp->args)
        {
            i = 0;
            while(tmp->args[i])
            {
                free(tmp->args[i]);
                i++;
            }
        	free(tmp->args);
        }
        if(tmp->red)
            free_red_list(tmp->red);
		if (tmp->herdoc_fd)
			close(tmp->herdoc_fd);
    free(tmp);
    }
}
void debug_print_tokens(t_token *head)
{
    t_token *t = head;
    while (t)
    {
        printf("TOKEN %p: type=%d value='%s' new_quote='%c' quoted=%d next=%p\n",
               (void*)t,
               t->type,
               t->value ? t->value : "(null)",
               t->new_quote ? t->new_quote : ' ',
               t->quoted,
               (void*)t->next);
        t = t->next;
    }
}

// void print_token(t_token *token)
// {
//     while(token)
//     {
//         printf("-> [%s]",token->value);
//         printf("-- [%d]\n",token->type);
//         printf("-- [%d]\n",token->quoted);
//         token=token->next;
//     }
// }

int main(int ac, char *av[], char **envp)
{
	char	*input;
	t_cmd	*cmd;
	t_token	*res;
	t_token	*tmp;
	t_env	*env_head;
	char	**env_arr;
	(void)ac;
	(void)av;
	int	a = 0;

	cmd = NULL;
	res = NULL;
	env_copy(envp, &env_head);
	ft_update_shelvl(env_head);
	env_head->exit_status = 0;
	print_tamazirt();
	while (1)
	{
		env_head->prompt = make_prompt();
		setup_signals();
		env_arr = env_to_arr(env_head);
		input = readline(env_head->prompt);
		if (g_signal == SIGINT)
		{
			env_head->exit_status = 1;
			g_signal = 0;
		}
		if (input == NULL)
		{
			free_args(env_arr);
			handle_end(env_head);
		}
		if (*input)
			add_history(input);
		if (check_synstax(input, env_head))
		{
			free(env_head->prompt);
			free_args(env_arr);
			continue ;
		}
		res = tokenize(input);
		expand_token_list(&res, env_arr, env_head);
		cmd = parse_cmd(res);
		tmp = res;
		while (tmp)
		{
			if (tmp->type == HEREDOC)
				a = tmp->quoted;
			tmp = tmp->next;
		}
		if (cmd)
			ft_execute(cmd, &env_head, input, a);
		// print_token(res);
		// print_cmd(cmd);
		free_cmd_list(cmd);
        free_token_list(res);
        free_token_list(tmp);
		free_args(env_arr);
		free(input);
		free(env_head->prompt);
		printf("--->>>>%d\n", env_head->exit_status);
	}
	free_env(env_head);
	free_args(env_arr);
	free(input);
	return (0);
}
