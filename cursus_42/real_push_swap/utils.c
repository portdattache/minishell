/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:02:33 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 10:14:06 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Va liberer la memoire allouee a la pile */
void	free_stack(t_node **stack)
{
	t_node	*tmp;
	t_node	*current;

	if (!*stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->suivant;
		current->num = 0;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}

/* Va servir a mesurer la Pile */
int	stack_len(t_node *stack)
{
	int	count;

	if (!stack)
		return (0);
	count = 0;
	while (stack)
	{
		stack = stack->suivant;
		count++;
	}
	return (count);
}
