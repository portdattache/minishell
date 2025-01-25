/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorythms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:06:11 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 10:17:42 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Algorithme pour 3 noeuds */
void	sort_3(t_node **a)
{
	t_node	*biggest;

	biggest = find_biggest(*a);
	if (biggest == *a)
		ra(a);
	else if (biggest == (*a)->suivant)
		rra(a);
	if ((*a)->num > (*a)->suivant->num)
		sa(a);
}
