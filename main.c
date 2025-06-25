/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:35:46 by rmouafik          #+#    #+#             */
/*   Updated: 2025/06/25 11:33:34 by rmouafik         ###   ########.fr       */
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

int	is_builtin(char **res, char *input, char *option, t_env **env_copy)
{
	if (!ft_strcmp(input, "env") || !ft_strcmp(input, "ENV"))
		return (ft_env(*env_copy));
	if (!ft_strcmp(input, "pwd") || !ft_strcmp(input, "PWD"))
		return (ft_pwd(*env_copy));
	if (!ft_strcmp(input, "cd"))
		return (ft_cd(option, env_copy));
	if (!ft_strcmp(input, "echo") || !ft_strcmp(input, "ECHO"))
		return (ft_echo(res, *env_copy));
	if (!ft_strcmp(input, "unset"))
		return (ft_unset(res, env_copy));
	if (!ft_strcmp(input, "exit"))
		return (ft_exit(res, env_copy));
	if (!ft_strcmp(input, "export"))
		return (ft_export(res, env_copy));
	return 0;
}

// void	ff(void)
// {
// 	system("leaks minishell");
// }

int main(int ac, char *av[], char **envp)
{
    char 	*input;
	char	**res;
    t_env	*env_head;

	env_copy(envp, &env_head);
    while(1)
    {
        input = readline("Minishell$> ");
        if(input == NULL)
            break ;
        if(*input)
            add_history(input);
		res = ft_split(input, ' ');
		is_builtin(res, res[0], res[1], &env_head);
    }
}
