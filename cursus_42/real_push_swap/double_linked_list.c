/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:37:09 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/24 11:46:37 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*add_to_empty(int number)
{
	t_node	*temp;

	temp = malloc(sizeof(t_node));
	if (temp == NULL)
		return (NULL);
	temp->precedent = NULL;
	temp->num = number;
	temp->suivant = NULL;
	return (temp);
}

t_node	*add_at_start(t_node *head, int number)
{
	t_node	*new_p;

	new_p = add_to_empty(number);
	if (new_p == NULL)
		return (NULL);
	else
	{
		new_p->suivant = head;
		if (head != NULL)
			head->precedent = new_p;
		return (new_p);
	}
}

t_node	*add_at_end(t_node *head, int number)
{
	t_node	*new_p;
	t_node	*last;

	new_p = add_to_empty(number);
	if (new_p == NULL)
		return (NULL);
	else
	{
		if (head == NULL)
			return (new_p);
		last = head;
		while (last->suivant != NULL)
			last = last->suivant;
		last->suivant = new_p;
		new_p->precedent = last;
		return (head);
	}
}

void	init_double_linked_list(int argc, char **argv, t_node **head, int start)
{
	long	temp;
	int		i;

	i = start;
	while (i < argc)
	{
		temp = atol(argv[i]);
		conditions_check(argv[i], *head, temp);
		if (*head == NULL)
			*head = add_to_empty(temp);
		else
		{
			*head = add_at_end(*head, temp);
			if (*head == NULL)
				return ;
		}
		i++;
	}
}
