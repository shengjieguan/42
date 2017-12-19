/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 10:25:03 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/19 16:17:09 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "../includes/checker.h"

int		ft_checker_check(t_env env)
{
	if (env.stack_b_size > 0)
	{
		ft_putstr("STACK B NOT EMPTY\n");
		return (0);
	}
	return (ft_checker_check_a(env));
}

int		ft_checker_check_a(t_env env)
{
	int	i;

	i = 0;
	while (i < env.stack_a_size - 1)
	{
		if (env.stack_a[i] < env.stack_a[i + 1])
		{
			ft_putnbr(env.stack_a[i]);
			ft_putstr(" < ");
			ft_putnbr(env.stack_a[i + 1]);
			ft_putstr(" (");
			ft_putnbr(i);
			ft_putstr(")\n");
			ft_putstr("CHECKER CHECK A =0\n");
			return (0);
		}
		++i;
	}
	ft_putstr("CHECKER CHECK A =1\n");
	return (1);
}

int		ft_checker_check_b(t_env env)
{
	int		state;
	t_env	e;

	if (env.stack_b_size == 1)
	{
		ft_putstr("CHECKER CHECK B =1\n");
		return (1);
	}
	ft_reverse_tab(&env.stack_b, env.stack_b_size);
	ft_memset(&e, 0, sizeof(t_env));
	e.stack_a = env.stack_b;
	e.stack_a_size = env.stack_b_size;
	env.stack_b_size = 0;
	if (!ft_checker_check(env))
	{
		ft_reverse_tab(&env.stack_b, e.stack_a_size);
		return (0);
	}
	state = ft_checker_check(e);
	ft_reverse_tab(&env.stack_b, e.stack_a_size);
	ft_putstr("CHECKER CHECK B =");
	ft_putnbr(state);
	ft_putendl("");
	return (state);
}
