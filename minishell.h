/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:30:31 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/25 11:35:56 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/libft.h"
# include <unistd.h>
# include <limits.h>

#define ERROR_ARG "minishell: exit: too many arguments\n"

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env *next;
} t_env;

// -------------- builtins ----------------

void	env_add_back(t_env **env_list, t_env *new_node);
void	env_copy(char **envp, t_env	**env_head);
void	ft_update_shelvl(t_env *env_list);
int 	ft_env(t_env *env_copy);
int		ft_pwd(t_env *env_copy);
int		ft_cd(char *path, t_env **env_copy);
int		ft_strcmp(char *s1, char *s2);
int		ft_echo(char **arr, t_env *env_copy);
int		ft_unset(char **arr, t_env **env_copy);
int 	ft_exit(char **arr, t_env **env_copy);
int		ft_export(char **arr, t_env **env_copy);

#endif

