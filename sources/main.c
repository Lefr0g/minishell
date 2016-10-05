/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 18:28:21 by amulin            #+#    #+#             */
/*   Updated: 2016/09/15 18:28:23 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av)
{
	t_msh_vars			v;
	t_builtin_handler	**builtin_func;
	
	msh_init_vars(&v);
	builtin_func = (t_builtin_handler**)ft_memalloc(sizeof(t_builtin_handler*));
	*builtin_func = NULL;
	msh_init_builtins_handlers(*builtin_func);

	(void)v;
	(void)av;
	/*
	i = -1;
	while (environ[++i])
		ft_printf("%s\n", environ[i]);
	*/

	if (ac != 1)
		ft_putstr("Invalid argument. This program doesn't take any.\n");
	else
	{
		msh_main_loop(&v, builtin_func);
	}
	return (0);
}
