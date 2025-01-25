/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:24:34 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/24 13:44:52 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_cheapest(t_node *stack)
{
	long	cheapest;
	t_node	*cheapest_node;

	if (!stack)
		return ;
	cheapest = LONG_MAX;
	while (stack)
	{
		if (stack->cost < cheapest)
		{
			cheapest = stack->cost;
			cheapest_node = stack;
		}
		stack = stack->suivant;
	}
	cheapest_node->cheapest = true;
}

void	set_position(t_node *stack)
{
	int	i;
	int	median;

	i = 0;
	if (!stack)
		return ;
	median = stack_len(stack) / 2;
	while (stack)
	{
		stack->position = i;
		if (i <= median)
			stack->above_median = true;
		else
			stack->above_median = false;
		stack = stack->suivant;
		++i;
	}
}

void	set_target_a(t_node *a, t_node *b)
{
	t_node	*current_b;
	t_node	*target_node;
	long	best_match_index;

	while (a)
	{
		best_match_index = LONG_MIN;
		current_b = b;
		while (current_b)
		{
			if (current_b->num < a->num && current_b->num > best_match_index)
			{
				best_match_index = current_b->num;
				target_node = current_b;
			}
			current_b = current_b->suivant;
		}
		if (best_match_index == LONG_MIN)
			a->cible = find_biggest(b);
		else
			a->cible = target_node;
		a = a->suivant;
	}
}

void	set_cost_a(t_node *a, t_node *b)
{
	int	len_a;
	int	len_b;

	len_a = stack_len(a);
	len_b = stack_len(b);
	while (a)
	{
		a->cost = a->position;
		if (!(a->above_median))
			a->cost = len_a - (a->position);
		if (a->cible->above_median)
			a->cost += a->cible->position;
		else
			a->cost += len_b - (a->cible->position);
		a = a->suivant;
	}
}

void	set_target_b(t_node *a, t_node *b)
{
	t_node	*current_a;
	t_node	*target_node;
	long	best_match;

	while (b)
	{
		best_match = LONG_MAX;
		current_a = a;
		while (current_a)
		{
			if (current_a->num > b->num && current_a->num < best_match)
			{
				best_match = current_a->num;
				target_node = current_a;
			}
			current_a = current_a->suivant;
		}
		if (best_match == LONG_MAX)
			b->cible = find_smallest(a);
		else
			b->cible = target_node;
		b = b->suivant;
	}
}
