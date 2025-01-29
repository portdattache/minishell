/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_checker_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:11:24 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/28 16:43:07 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/* Va servir a trouver la prochaine ligne dans la str */
int	found_newline(t_lst *lst)
{
	int	i;

	if (lst == NULL)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->str_buff[i] && i < BUFFER_SIZE)
		{
			if (lst->str_buff[i] == '\n')
				return (1);
			++i;
		}
		lst = lst->next;
	}
	return (0);
}

/* Va trouver le dernier noeud de la liste */
t_lst	*dernier_noeud_2(t_lst *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/* Va servir a copier la str */
void	copy_str(t_lst *lst, char *str)
{
	int	i;
	int	k;

	if (lst == NULL)
		return ;
	k = 0;
	while (lst)
	{
		i = 0;
		while (lst->str_buff[i])
		{
			if (lst->str_buff[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = lst->str_buff[i++];
		}
		str[k] = '\0';
		lst = lst->next;
	}
}

/* Va servir a mesurer la taille de la prochaine ligne de la str */
int	len_to_newline(t_lst *lst)
{
	int	i;
	int	len;

	if (NULL == lst)
		return (0);
	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->str_buff[i])
		{
			if (lst->str_buff[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		lst = lst->next;
	}
	return (len);
}

/* Va servir a desallouer la memoire attribuee a la liste */
void	dealloc(t_lst **lst, t_lst *clean_node, char *buf)
{
	t_lst	*tmp;

	if (NULL == *lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->str_buff);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
	if (clean_node->str_buff[0])
		*lst = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
