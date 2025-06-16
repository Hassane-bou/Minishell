/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:35:46 by rmouafik          #+#    #+#             */
/*   Updated: 2025/06/16 12:43:20 by rmouafik         ###   ########.fr       */
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

int	is_builtin(char *input, char *option, t_env **env_copy)
{
	if (!ft_strcmp(input, "env"))
		return (ft_env(*env_copy));
	if (!ft_strcmp(input, "pwd"))
		return (ft_pwd(*env_copy));
	if (!ft_strcmp(input, "cd"))
		return (ft_cd(option, env_copy));
	return 0;
}

int main(int ac, char *av[], char **envp)
{
    char 	*input;
	char	**res;
    t_env	*env_head;

	env_copy(envp, &env_head);
    while(1)
    {
        input = readline("Minishell> ");
        if(input == NULL)
            break ;
        if(*input)
            add_history(input);
		res = ft_split(input, ' ');
		is_builtin(res[0], res[1], &env_head);
    }
}
