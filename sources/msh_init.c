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

#include "minishell.c"

int		msh_init_builtins(t_msh_vars *v)
{
	if (!(v->builtins =
				(char**)malloc(sizeof(char*) * MSH_BUILTINS_ARRAY_SIZE)))
		return (-1);
	ft_strdup(v->builtins[0], "echo");
	ft_strdup(v->builtins[1], "cd");
	ft_strdup(v->builtins[2], "setenv");
	ft_strdup(v->builtins[3], "unsetenv");
	ft_strdup(v->builtins[4], "env");
	ft_strdup(v->builtins[5], "exit");
	v->builtins[6] = ft_strnew(1);
	return (0);
}

int		msh_init_vars(t_msh_vars *v)
{
	extern char	**environ;

	v->environ = ft_strarray_dup(environ);
	v->locales = (char**)malloc(sizeof(char*));
	ft_bzero(&(v->locales[0]), 1);
	ft_msh_init_builtins(v);
	return (0);
}
