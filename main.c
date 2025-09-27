/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:35:46 by rmouafik          #+#    #+#             */
/*   Updated: 2025/09/27 12:10:20 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	check_synstax(char *input, t_env *head)
{
	if (check_all_syntaxe(input) == 1)
	{
		head->exit_status = 258;
		return (1);
	}
	else
		return (0);
}

int	init_env(char **envp, t_env **env_head)
{
	env_copy(envp, env_head);
	ft_update_shelvl(*env_head);
	(*env_head)->exit_status = 0;
	print_tamazirt();
	return (0);
}

int	handle_input(t_help *var, t_env *env_head, char ***env_arr)
{
	env_head->prompt = make_prompt();
	setup_signals();
	*env_arr = env_to_arr(env_head);
	var->input = readline(env_head->prompt);
	if (g_signal == SIGINT)
	{
		env_head->exit_status = 1;
		g_signal = 0;
	}
	if (var->input == NULL)
	{
		free_args(*env_arr);
		handle_end(env_head);
	}
	if (var->input)
		add_history(var->input);
	if (check_synstax(var->input, env_head))
	{
		free(env_head->prompt);
		free_args(*env_arr);
		return (1);
	}
	return (0);
}

void	process_cmd(t_help *var, t_env *env_head, char **env_arr)
{
	t_cmd	*cmd;
	t_token	*res;

	res = tokenize(var->input);
	expand_token_list(&res, env_arr, env_head);
	cmd = parse_cmd(res);
	var->temp = res;
	while (var->temp)
	{
		if (var->temp->type == HEREDOC)
			var->quoted = var->temp->quoted;
		var->temp = var->temp->next;
	}
	if (cmd)
		ft_execute(cmd, &env_head, var->quoted);
	free_cmd_list(cmd);
	free_token_list(res);
	free_token_list(var->temp);
	free_args(env_arr);
	free(var->input);
	free(env_head->prompt);
}

int	main(int ac, char *av[], char **envp)
{
	t_help	var;
	t_env	*env_head;
	char	**env_arr;

	(void)ac;
	(void)av;
	var.quoted = 0;
	init_env(envp, &env_head);
	while (1)
	{
		if (handle_input(&var, env_head, &env_arr))
			continue ;
		process_cmd(&var, env_head, env_arr);
	}
	free_env(env_head);
	free_args(env_arr);
	free(var.input);
	return (0);
}
