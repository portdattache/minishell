/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:38:27 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/29 10:23:18 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 == *str2 && *str1)
	{
		++str1;
		++str2;
	}
	return (*str1 - *str2);
}

/* Va liberer la memoire des piles a & b en cas d'erruers */
static void	erreur(t_node **a, t_node **b)
{
	free_stack(a);
	free_stack(b);
	ft_printf("Error\n");
	exit(1);
}

/* Va verifier si les commandes sont valides */
static void	verifs_commandes(t_node **a, t_node **b, char *command)
{
	if (!ft_strcmp(command, "pa\n"))
		push(a, b);
	else if (!ft_strcmp(command, "pb\n"))
		push(b, a);
	else if (!ft_strcmp(command, "sa\n"))
		swap(a);
	else if (!ft_strcmp(command, "sb\n"))
		swap(b);
	else if (!ft_strcmp(command, "ss\n"))
		ss(a, b, true);
	else if (!ft_strcmp(command, "ra\n"))
		rotate(a);
	else if (!ft_strcmp(command, "rb\n"))
		rotate(b);
	else if (!ft_strcmp(command, "rr\n"))
		rr(a, b, true);
	else if (!ft_strcmp(command, "rra\n"))
		reverse_rotate(a);
	else if (!ft_strcmp(command, "rrb\n"))
		reverse_rotate(b);
	else if (!ft_strcmp(command, "rrr\n"))
		rrr(a, b, true);
	else
		erreur(a, b);
}

int	main(int argc, char **argv)
{
	t_node	*a;
	t_node	*b;
	char	*next_line;
	int		len;

	a = NULL;
	b = NULL;
	if (argc == 1)
		return (0);
	else if (argc == 2)
		argv = ft_split(argv[1], ' ');
	init_dll(argc, argv, &a, 1);
	len = taille_pile(a);
	next_line = get_next_line_checker(STDIN_FILENO);
	while (next_line)
	{
		verifs_commandes(&a, &b, next_line);
		next_line = get_next_line_checker(STDIN_FILENO);
	}
	if (pile_triee(a) && taille_pile(a) == len)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	free(a);
}
