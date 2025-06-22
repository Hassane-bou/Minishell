/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:39:16 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/22 12:17:10 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/****************HANDLE QUtes****************/
// int handle_quotes(char *input,int i,t_token **head)
// {
//     char quote_char;
//     int start;
//     t_token *new_token = NULL;
//     char *word;

//     quote_char=input[i];
//     i++;
//     start = i;
//     while(input[i] && input[i] != quote_char)
//         i++;
//     word = ft_substr(input,start,i - start);
//     new_token = cretae_token(word,WORD);
//     append_token(head,new_token);
//     if(input[i] == quote_char)
//         i++;
//     return (i);
// }

int	check_pipe1_syntaxe(char *input, int i)
{
	int	j;

	while (isspace(input[i]))
		i++;
	if (input[i] == '|' && input[i + 1] && input[i + 1] == '|')
		return (1);
	if (input[i] == '|')
	{
		j = i + 1;
		while (isspace(input[j]))
			j++;
		if (input[j] == '|')
			return (1);
	}
	return (0);
}

int	check_pipe_syntaxe(char *input)
{
	int	i;
	int	end_input;
	int	j;

	j = 0;
	end_input = strlen(input) - 1;
	i = 0;
	while (isspace(input[i]))
		i++;
	if (input[i] == '|')
		return (1);
	while (end_input >= 0 && isspace(input[end_input]))
		end_input--;
	if (input[end_input] == '|')
		return (1);
	while (input[i])
	{
		if (check_pipe1_syntaxe(input, i))
			return (1);
		i++;
	}
	return (0);
}

/*****************check syntaxe redirection**************/

// int check_q(char *input,int i)
// {
// 	char q;
// 	q = 0;
// 	if((input[i] == '\'' || input[i] == '"') && !q)
// 	{
// 		q = input[i];
// 		i++;
// 		while(input[i] && input[i] != q)
// 			i++;
// 		if(input[i] == q)
// 		{
// 			q = 0;
// 			i++;
// 		}
// 	}
// 	return(i);
// }
// int check_red(char *input,int i)
// {
// 	char redirect;
// 	int count;

// 	if(input[i] == '>' || input[i] == '<')
// 	{
// 		redirect = input[i];
// 		count = 0;
// 		while(input[i] == redirect)
// 		{
// 			count++;
// 			i++;
// 		}
// 		if(count > 2)
// 			return 1;
// 		while(isspace(input[i]))
// 			i++;
// 		 if(input[i] == '\0' || input[i] == '|' || input[i] == '>' || input[i] == '<')
//             return 1;
// 	}
// 	return(i);
// }
// int check_redirection_syntaxe(char *input)
// {
//     int i = 0;
//     int count;
//     int new_i = 0;
//     while(input[i])
//     {
// 		new_i = check_q(input,i);
//         if (new_i != i)
// 		{
// 			i = new_i;
//             continue;
// 		}
// 		if(check_red(input,i) ==  1)
// 			return 1;
// 		if(check_red(input,i) != i)
// 			i = check_red(input,i);
//         else
//             i++;   
//     }
//    return 0;
// }
int main()
{
	char *str = " | ls -l | hello";
	int i = check_pipe_syntaxe(str);
	printf("%d\n",i);
	
}