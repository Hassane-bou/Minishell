/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:31:29 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/14 09:41:19 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error_function()
{
    write(2,"erreur\n",7);
    exit(1);
}
t_list	*ft_lstnew(char *content)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->text = content;
	list->next = NULL;
	return (list);
}
void	ft_add_back_lst(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		new->next = NULL;
	}
}

// t_list *tokenize(char *input)
// {
//     int j;
//     char **split;
//     t_list *node;
//     t_list *list;
 
//     split = ft_split(input, '|');
//     if(!split)
//         error_function();
//     list = NULL;
//     j=0;
//     while(split[j])
//     {
//         node = ft_lstnew(split[j]);
//         if(!node)
//             error_function();
//         ft_add_back_lst(&list, node);
//         j++;
//     }
//     return (list);
// }