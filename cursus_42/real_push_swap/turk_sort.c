/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:17:31 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 11:26:26 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_nodes_a(t_node *a, t_node *b)
{
	set_position(a);
	set_position(b);
	set_target_a(a, b);
	set_cost_a(a, b);
	set_cheapest(a);
}

static void	init_nodes_b(t_node *a, t_node *b)
{
	set_position(a);
	set_position(b);
	set_target_b(a, b);
}

static void	move_a_to_b(t_node **a, t_node **b)
{
	t_node	*cheapest;

	cheapest = return_cheapest(*a);
	if (!cheapest)
		return ;
	if (!cheapest->cible)
		return ;
	if (cheapest->above_median && cheapest->cible->above_median)
		rotate_both(a, b, cheapest);
	else if (!cheapest->above_median && !cheapest->cible->above_median)
		rev_rotate_both(a, b, cheapest);
	prep_for_push(a, cheapest, 'a');
	prep_for_push(b, cheapest->cible, 'b');
	pb(a, b);
}

static void	move_b_to_a(t_node **a, t_node **b)
{
	prep_for_push(a, ((*b)->cible), 'a');
	pa(a, b);
}

/* Algorithme de tri turc lorsqu'il y a plus de 3 noeuds */
void	turk_algo(t_node **a, t_node **b)
{
	int	len_a;

	len_a = stack_len(*a);
	if (len_a-- > 3 && !stack_sorted(*a))
		pb(a, b);
	if (len_a-- > 3 && !stack_sorted(*a))
		pb(a, b);
	while (len_a-- > 3 && !stack_sorted(*a))
	{
		init_nodes_a(*a, *b);
		move_a_to_b(a, b);
	}
	sort_3(a);
	while (*b)
	{
		init_nodes_b(*a, *b);
		move_b_to_a(a, b);
	}
	set_position(*a);
	smallest_on_top(a);
}
