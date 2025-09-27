/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:52:50 by rmouafik          #+#    #+#             */
/*   Updated: 2025/09/25 12:15:17 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*make_prompt(void)
{
	char	*pwd;
	char	*suffix;
	char	*colored;
	char	*final_prompt;

	pwd = getcwd(NULL, 0);
	suffix = ft_strjoin(pwd, "$> ");
	colored = ft_strjoin("\033[1;32m", suffix);
	final_prompt = ft_strjoin(colored, "\001\033[0m\002");
	free(pwd);
	free(suffix);
	free(colored);
	return (final_prompt);
}
