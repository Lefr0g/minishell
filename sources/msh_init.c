/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 18:18:54 by amulin            #+#    #+#             */
/*   Updated: 2016/09/15 18:27:39 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_init_builtins(t_msh_vars *v)
{
	if (!(v->builtins =
				(char**)malloc(sizeof(char*) * MSH_BUILTINS_ARRAY_SIZE)))
		return (-1);
	v->builtins[0] = ft_strdup("echo");
	v->builtins[1] = ft_strdup("cd");
	v->builtins[2] = ft_strdup("setenv");
	v->builtins[3] = ft_strdup("unsetenv");
	v->builtins[4] = ft_strdup("env");
	v->builtins[5] = ft_strdup("exit");
	v->builtins[6] = ft_strnew(1);
	return (0);
}

int		msh_init_vars(t_msh_vars *v)
{
	extern char	**environ;

	v->environ = ft_strarray_dup(environ);
	v->locales = (char**)malloc(sizeof(char*));
	ft_bzero(&(v->locales[0]), 1);
	msh_init_builtins(v);
	return (0);
}
