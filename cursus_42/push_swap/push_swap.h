/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:15:30 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 12:16:30 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_node
{
	int				number;
	int				index;
	int				cost;
	bool			above_median;
	bool			cheapest;
	struct s_node	*next;
	struct s_node	*prev;
	struct s_node	*target;
}					t_node;

// ***** MAIN *****

// main
int					main(int argc, char **argv);

// ***** COMMANDS *****

// push
void				pa(t_node **stack_a, t_node **stack_b);
void				pb(t_node **stack_a, t_node **stack_b);

// reverse_rotate
void				rra(t_node **stack_a);
void				rrb(t_node **stack_b);
void				rrr(t_node **stack_a, t_node **stack_b);
void				rev_rotate_both(t_node **a, t_node **b, t_node *cheapest);

// rotate
void				ra(t_node **stack_a);
void				rb(t_node **stack_b);
void				rr(t_node **stack_a, t_node **stack_b);
void				rotate_both(t_node **a, t_node **b, t_node *cheapest);

// swappedyswaps
void				sa(t_node **stack_a);
void				sb(t_node **stack_b);
void				ss(t_node **stack_a, t_node **stack_b);

// ***** PUSHI_PUSHI_SWAP *****

// atob
void				set_target_a(t_node *a, t_node *b);
void				set_cost_a(t_node *a, t_node *b);

// btoa
void				set_target_b(t_node *a, t_node *b);

// check
bool				stack_sorted(t_node *stack);
int					sorted_check(t_node **list);

// dll
void				init_dll(int argc, char **argv, t_node **head, int start);
t_node				*add_to_empty(int number);
t_node				*add_at_end(t_node *head, int number);
t_node				*add_at_start(t_node *head, int number);

// errors
void				safety_check(char *s, t_node *a, long n);
void				free_errors(t_node **a);
void				free_stack(t_node **stack);

// find
t_node				*find_biggest(t_node *stack);
t_node				*find_smallest(t_node *stack);
t_node				*find_last(t_node *stack);
int					stack_len(t_node *stack);
t_node				*return_cheapest(t_node *stack);

// utils
void				set_index(t_node *stack);
void				set_chpst(t_node *stack);
void				prep_for_push(t_node **stack, t_node *top_node,
						char stack_name);
void				smallest_on_top(t_node **a);

// sort_3
void				sort_3(t_node **a);

// turk_sort
void				turk_algo(t_node **a, t_node **b);

// others
char				**ft_split(char const *s, char c);
void				ft_putstr(char *str);

#endif