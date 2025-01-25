/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:14:27 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/24 14:24:57 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_node **dest, t_node **source)
{
	t_node	*to_push;

	if (!*source)
		return ;
	to_push = *source;
	*source = (*source)->suivant;
	if (*source)
		(*source)->precedent = NULL;
	to_push->precedent = NULL;
	if (!*dest)
	{
		*dest = to_push;
		to_push->suivant = NULL;
	}
	else
	{
		to_push->suivant = *dest;
		to_push->suivant->precedent = to_push;
		*dest = to_push;
	}
}

void	pb(t_node **stack_a, t_node **stack_b)
{
	push(stack_b, stack_a);
	ft_printf("pb\n");
}

void	pa(t_node **stack_a, t_node **stack_b)
{
	push(stack_a, stack_b);
	ft_printf("pa\n");
}
void	prep_for_push(t_node **stack, t_node *top_node, char stack_name)
{
	if (!stack || !top_node)
		return ;
	while (*stack != top_node)
	{
		if (stack_name == 'a')
		{
			if (top_node->above_median)
			{
				ra(stack);
			}
			else
			{
				rra(stack);
			}
		}
		else if (stack_name == 'b')
		{
			if (top_node->above_median)
				rb(stack);
			else
				rrb(stack);
		}
	}
}
