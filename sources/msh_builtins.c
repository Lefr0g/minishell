/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 18:07:18 by amulin            #+#    #+#             */
/*   Updated: 2016/09/26 17:15:09 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_handle_exit(char **args, char **env)
{
	(void)args;
	(void)env;
	exit(0);
	return (0);
}

int		msh_handle_echo(char **args, char **env)
{
	int		i;
	int		no_newline;
	(void)env;

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

/*
**	Basic options parser for builtin
**	Each char included in 'options' is searched within each 'args' starting
**	with '-'
**	The flags are returned in order right to left as bits flip within the int
**	Option precedence is not managed by this function
*/
int		msh_parse_cd_options(char **args, char *options)
{
	int		i;
	int		j;
	int		p_opt;
	int		flag;

	flag = 0;
	i = 1;
	p_opt = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][0] == '-')
			{
				flag = 1;
				if (args[i][j] == 'P')
					p_opt = 1;
				else if (args[i][j] == 'L')
					p_opt = 0;
				else
					return (-1);
			}
			j++;
		}
		if (flag)
			ft_strdel(args[i])
	}
	return (p_opt);
}

int		msh_handle_cd(char **args, char **env)
{
	char	*target;
	char	*home;
	int		option;
	
	home = msh_getenv("HOME", env);

	option = msh_parse_cd_options(args);

//	ft_printf("Home is '%s'\n", home);

	target = NULL;
	if (!args[1])
		target = ft_strdup(home);
	else if (ft_strchr(args[1], '~'))
		target = ft_find_and_replace(args[1], "~", 0, home);
	else
		target = ft_strdup(args[1]);
	ft_printf("calling chdir on %s\n", target);
	
	if (chdir(target))
		ft_printf("cd: no such file or directory: '%s'\n", args[1]);
	ft_strdel(&target);
	ft_strdel(&home);
	return (0);
}

int		msh_handle_default(char **args, char **env)
{
	(void)args;
	(void)env;
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
	v->builtin_func[i](args, v->environ);
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
