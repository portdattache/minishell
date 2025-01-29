/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swaps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:03:09 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/29 10:18:10 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	swap(t_node **head)
{
	if (!*head || !(*head)->suivant)
		return ;
	*head = (*head)->suivant;
	(*head)->precedent->suivant = (*head)->suivant;
	if ((*head)->suivant)
		(*head)->suivant->precedent = (*head)->precedent;
	(*head)->suivant = (*head)->precedent;
	(*head)->precedent = NULL;
}

void	sa(t_node **stack_a)
{
	swap(stack_a);
	ft_printf("sa\n");
}

void	sb(t_node **stack_b)
{
	swap(stack_b);
	ft_printf("sb\n");
}

void	ss(t_node **stack_a, t_node **stack_b, bool print)
{
	sa(stack_a);
	sb(stack_b);
	if (!print)
		ft_printf("ss\n");
}
