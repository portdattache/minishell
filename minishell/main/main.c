/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:09:48 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/01 09:47:43 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	t_shell	shell;

	init_shell(&shell);
	prompt(&shell);
	cleanup_shell(&shell);
	rl_clear_history();
	return (0);
}
