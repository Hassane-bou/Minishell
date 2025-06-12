/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:35:46 by rmouafik          #+#    #+#             */
/*   Updated: 2025/06/12 13:30:40 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main()
// {
//     char *input;
    
//     while(1)
//     {
//         input = readline("Minishell> ");
//         if(input == NULL)
//             break;
//         if(*input)
//             add_history(input);
//     }
//     printf("%s\n",input);
//     // free(input);
// }


int main(int ac, char *av[], char **envp)
{
	t_env *env_head = NULL;
    env_copy(envp, &env_head);
    ft_update_shelvl(env_head);
	t_env *tmp = env_head;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
