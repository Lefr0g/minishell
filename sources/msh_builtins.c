/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 18:07:18 by amulin            #+#    #+#             */
/*   Updated: 2016/09/16 17:15:05 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_handle_exit(char **args)
{
	(void)args;
	exit(0);
	return (0);
}

int		msh_handle_echo(char **args)
{
	int		i;
	int		no_newline;

	i = 0;
	no_newline = 0;
	while (MSH_DEBUG_MODE && args[i])
	{
		ft_printf("args[%d] = %s\n", i, args[i]);
		i++;
	}
	if (!ft_strcmp(args[1], "-n"))
	{
		no_newline = 1;
		args[1][0] = '\0';
		i = 2;
	}
	else
		i = 1;
	while (args[i])
	{
		ft_putstr(args[i]);
		ft_putchar(' ');
		i++;
	}
	if (!no_newline)
		ft_putchar('\n');
	return (0);
}

int		msh_handle_default(char **args)
{
	(void)args;
	ft_printf("Default built-in handler\n");
	return (0);
}

/*
**	Call the relevant routine for the given command
*/

int		msh_handle_builtin(char **args, t_msh_vars *v)
{
	int	i;

	if ((i = msh_get_builtin_index(args[0], v->builtin_name)) == -1)
	{
		ft_putstr_fd("Error: built-in not found\n", STDERR_FILENO);
		return (-1);
	}
	else if (MSH_DEBUG_MODE)
		ft_printf("%s%s%s is a built-in\n", ANSI_FG_CYAN, args[0], ANSI_RESET);
	v->builtin_func[i](args);
	return (0);
}

/*
**	Returns a pointer to the builtin name in the builtins table if true,
**	or NULL.
*/

char	*msh_is_builtin(char *cmd, char **builtins)
{
	int	i;

	i = -1;
	while (++i < MSH_BUILTINS_ARRAY_SIZE)
		if (!ft_strcmp(cmd, builtins[i]))
			return (builtins[i]);
	return (NULL);
}

/*
**	Returns the index of the command in the builtins table, to be used to
**	call the relevant handle function via its pointer
*/

int		msh_get_builtin_index(char *cmd, char **builtins)
{
	int	i;

	if (!msh_is_builtin(cmd, builtins))
		return (-1);
	i = 0;
	while (ft_strcmp(cmd, builtins[i]))
		i++;
	return (i);
}
