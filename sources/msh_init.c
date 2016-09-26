/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 18:18:54 by amulin            #+#    #+#             */
/*   Updated: 2016/09/16 17:09:54 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_init_builtins_names(t_msh_vars *v)
{
	if (!(v->builtin_name =
				(char**)malloc(sizeof(char*) * MSH_BUILTINS_ARRAY_SIZE)))
		return (-1);
	v->builtin_name[0] = ft_strdup(MSH_BUILTIN_0);
	v->builtin_name[1] = ft_strdup(MSH_BUILTIN_1);
	v->builtin_name[2] = ft_strdup(MSH_BUILTIN_2);
	v->builtin_name[3] = ft_strdup(MSH_BUILTIN_3);
	v->builtin_name[4] = ft_strdup(MSH_BUILTIN_4);
	v->builtin_name[5] = ft_strdup(MSH_BUILTIN_5);
	v->builtin_name[6] = ft_strnew(1);
	return (0);
}

int		msh_init_builtins_handlers(t_msh_vars *v)
{
	if (!(v->builtin_func =
				(t_builtin_handler*)malloc(sizeof(t_builtin_handler)
					* MSH_BUILTINS_ARRAY_SIZE)))
		return (-1);
	v->builtin_func[0] = &msh_handle_echo;
	v->builtin_func[1] = &msh_handle_cd;
	v->builtin_func[2] = &msh_handle_default;
	v->builtin_func[3] = &msh_handle_default;
	v->builtin_func[4] = &msh_handle_default;
	v->builtin_func[5] = &msh_handle_exit;
	v->builtin_func[6] = &msh_handle_default;
	return (0);
}

int		msh_init_vars(t_msh_vars *v)
{
	extern char	**environ;

	v->environ = ft_strarray_dup(environ);
	v->locales = (char**)malloc(sizeof(char*));
	ft_bzero(&(v->locales[0]), 1);
	msh_init_builtins_names(v);
	msh_init_builtins_handlers(v);
	return (0);
}
