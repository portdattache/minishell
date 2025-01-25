/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:48:13 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 11:31:05 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Va verifier la validite des caracteres */
int	error_synthax(char *str)
{
	if (!(*str == '+' || *str == '-' || (ft_isdigit(*str))))
		return (1);
	if ((*str == '+' || *str == '-') && !(ft_isdigit(*str)))
		return (1);
	while (++*str)
	{
		if (!(ft_isdigit(*str)))
			return (1);
	}
	return (0);
}

/* Va verifier qu'il n'y a pas de doublons */
int	error_duplicate(t_node *a, int n)
{
	if (!a)
		return (0);
	while (a)
	{
		if (a->num == n)
			return (1);
		a = a->suivant;
	}
	return (0);
}

void	safety_check(char *s, t_node *a, long n)
{
	if (n < INT_MIN || n > INT_MAX)
		free_errors(&a);
	if (error_synthax(s) != 0)
		free_errors(&a);
	if (error_duplicate(a, n) != 0)
		free_errors(&a);
}

void	free_errors(t_node **a)
{
	free_stack(a);
	ft_printf("Error\n");
	exit(1);
}
