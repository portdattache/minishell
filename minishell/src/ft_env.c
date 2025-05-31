/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:35:45 by garside           #+#    #+#             */
/*   Updated: 2025/05/31 15:30:13 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_data *data)
{
	t_env	*i;

	i = data->env;
	while (i)
	{
		ft_printf("%s=%s\n", i->name, i->content);
		i = i->next;
	}
	return (0);
}
