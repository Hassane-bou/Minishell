/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:35:46 by rmouafik          #+#    #+#             */
/*   Updated: 2025/06/28 13:21:19 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return 1;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return (1);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	is_builtin(t_cmd *cmd, t_env **env_copy)
{
	if (!ft_strcmp(cmd->cmd, "env") || !ft_strcmp(cmd->cmd, "ENV"))
		return (ft_env(*env_copy));
	if (!ft_strcmp(cmd->cmd, "pwd") || !ft_strcmp(cmd->cmd, "PWD"))
		return (ft_pwd(*env_copy));
	if (!ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(cmd->args[0], env_copy));
	if (!ft_strcmp(cmd->cmd, "echo") || !ft_strcmp(cmd->cmd, "ECHO"))
		return (ft_echo(cmd->args, *env_copy));
	if (!ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset(cmd->args, env_copy));
	if (!ft_strcmp(cmd->cmd, "exit"))
		return (ft_exit(cmd->args, env_copy));
	if (!ft_strcmp(cmd->cmd, "export"))
		return (ft_export(cmd->args, env_copy));
	return 0;
}

char **env_to_arr(t_env *env_head)
{
	char	**env_arr;

	int	i = 0;
	env_arr = malloc(sizeof(char **) * 1337);
	while (env_head)
	{
		char *tmp = ft_strjoin(env_head->key, "=");
		env_arr[i] = ft_strjoin(tmp, env_head->value);
		free(tmp);
		i++;
		env_head = env_head->next;
	}
	return (env_arr);
}

// void	ff(void)
// {
// 	system("leaks minishell");
// }

int main(int ac, char *av[], char **envp)
{
    char 	*input;
	char	**env_arr;
	t_token *res;
    t_cmd	*cmd;
    t_env	*env_head;

	env_copy(envp, &env_head);
    while(1)
    {
        input = readline("Minishell$> ");
        if(input == NULL)
            break ;
        if(*input)
            add_history(input);
		res = tokenize(input);
        cmd = parse_cmd(res);
		env_arr = env_to_arr(env_head);
		ft_execute(cmd, );
    }
}
