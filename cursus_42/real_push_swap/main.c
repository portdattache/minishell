/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:43:41 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 11:44:58 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static size_t	ft_arrlen(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}

static void	free_str_array(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static void	init_split(int argc, char **argv, t_node **stack)
{
	argv = ft_split(argv[1], ' ');
	argc = ft_arrlen(argv);
	init_double_linked_list(argc, argv, stack, 0);
	free_str_array(argv);
}

static void	init_algo(t_node **stack_a, t_node **stack_b)
{
	if (stack_len(*stack_a) == 2)
		sa(stack_a);
	else if (stack_len(*stack_a) == 3)
		sort_3(stack_a);
	else
		turk_algo(stack_a, stack_b);
}

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 2)
		init_split(argc, argv, &stack_a);
	else if (argc > 2)
		init_double_linked_list(argc, argv, &stack_a, 1);
	else
		return (1);
	if (!stack_sorted(stack_a))
		init_algo(&stack_a, &stack_b);
	free_stack(&stack_a);
	return (0);
}
