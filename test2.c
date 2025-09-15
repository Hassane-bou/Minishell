/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 09:35:22 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/14 10:45:19 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>
#include <string.h>

// char *str = "'hello' | 'hello'";

int check_synatxe_pipe(char *input)
{
    int i =0;
    int len = strlen(input);
    int end_input = len - 1;
    int quote = 0;
    
    while(input[i])
    {
        if(isspace(input[i]))
            i++;
        if(input[i] == '|')
            return 1;
        while(input[end_input] >= 0 && isspace(input[end_input]))
            end_input--;
        if(input[end_input] == '|')
            return 1;
        while(input[i])
        {
            if((input[i] =='\'' || input[i] == '"') && !quote)
                quote = input[i];
            else 
                quote = 0;
            if(!quote)
            {
                if(input[i] == '|' && input[i+1] == '|')
                    return 1; 
            }
            i++;       
        } 
        i++;
    }
    return 0;
}
int main()
{
    char *str = "'hello' | 'hello'";
    if(check_synatxe_pipe(str))
        printf("erreur\n");
    else
        printf("is valid\n");
    return 0;
}