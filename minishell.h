/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:30:31 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/12 13:18:38 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/libft.h"
# include <unistd.h>

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env *next;
} t_env;

void	env_add_back(t_env **env_list, t_env *new_node);
void	env_copy(char **envp, t_env	**env_head);
void	ft_update_shelvl(t_env *env_list);

#endif