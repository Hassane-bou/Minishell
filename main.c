/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:35:46 by rmouafik          #+#    #+#             */
/*   Updated: 2025/06/12 10:38:21 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(int ac, char *av[], char **envp)
// {
// 	int		i;
// 	int		pos;
// 	t_env	**env_copy;
// 	char	*str_value;

// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	env_copy = malloc(sizeof(t_env *) * i);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		env_copy[i] = malloc(sizeof(t_env));
// 		str_value = ft_strchr(envp[i], '=');
// 		pos = str_value - envp[i];
// 		env_copy[i]->key = ft_substr(envp[i], 0, pos);
// 		env_copy[i]->value = ft_strdup(str_value + 1);
// 		printf("%s=%s\n", env_copy[i]->key, env_copy[i]->value);
// 		i++;
// 	}
// }

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	env_add_back(t_env **env_list, t_env *new_node)
{
	t_env	*tmp;

	if (!env_list || !new_node)
		return ;
	if (*env_list == NULL)
		*env_list = new_node;
	else
	{
		tmp = ft_lstlast_env(*env_list);
		tmp->next = new_node;
	}
}

// int main(int ac, char *av[], char **envp)
// {
// 	int		i;
// 	int		pos;
// 	t_env	*env_head;
// 	t_env	*env_node;
// 	char	*ptr_value;

// 	i = 0;
// 	env_head = NULL;
// 	while (envp[i])
// 	{
// 		env_node = malloc(sizeof(t_env));
// 		ptr_value = ft_strchr(envp[i], '=');
// 		pos = ptr_value - envp[i];
// 		env_node->key = ft_substr(envp[i], 0, pos);
// 		env_node->value = ft_strdup(ptr_value + 1);
// 		env_node->next = NULL;
// 		env_add_back(&env_head, env_node);
// 		printf("%s=%s\n", env_node->key, env_node->value);
// 		i++;
// 	}
// }
int main()
{
    char *input;
    
    while(1)
    {
        input = readline("Minishell> ");
        if(input == NULL)
            break;
        if(*input)
            add_history(input);
    }
    printf("%s\n",input);
    // free(input);
}