/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:21:52 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 11:31:59 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	smallest_on_top(t_node **a)
{
	while ((*a)->num != find_smallest(*a)->num)
	{
		if (find_smallest(*a)->above_median)
			ra(a);
		else
			rra(a);
	}
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
