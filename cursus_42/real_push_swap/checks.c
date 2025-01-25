/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:27:01 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 11:32:27 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	stack_sorted(t_node *stack)
{
	if (!stack)
		return (1);
	while (stack->suivant)
	{
		if (stack->num > stack->suivant->num)
			return (false);
		stack = stack->suivant;
	}
	return (true);
}

int	sorted_check(t_node **list)
{
	t_node	*ptr;

	if (*list == NULL)
		return (1);
	ptr = (*list)->suivant;
	while (ptr != *list)
	{
		if (ptr->num > ptr->suivant->num)
			return (0);
		ptr = ptr->suivant;
	}
	return (1);
}
