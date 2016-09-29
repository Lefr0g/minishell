/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 18:07:18 by amulin            #+#    #+#             */
/*   Updated: 2016/09/27 19:19:59 by amulin           ###   ########.fr       */
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
**	This function parses the input args for cd, searching for options.
**	'mode' is a pointer to a 1 character string, containing the letter L or P
**	if a valid option or no option is specified. An unsupported option will point
**	'mode' to an empty string.
**	Upon success, the function returns a pointer to the argument to be used as
**	argument for chdir(). Notice that if no argument is given the function returns
**	NULL, which doesn't mean a problem occured.
**	Valid options will be deleted from the input 'args' string array
*/
char	*msh_parse_cd(char **args, char *mode)
{
	char	**supported_options;
	char	**parsed_options;
	char	ret;
	int		i;

	parsed_options = NULL;
//	Defining supported options
	supported_options = ft_strarray_new(3);
	supported_options[0] = ft_strdup("P");
	supported_options[1] = ft_strdup("L");
	supported_options[2] = ft_strdup("");
//	Parsing options
	ret = ft_parse_options_keep_doubles(args, supported_options, &parsed_options);
	ft_strarray_del(&supported_options);
	if (ret) // Invalid option abort
	{
		ft_printf("%s: cd: -%c: invalid option\n", PROG_NAME, ret);
		ft_printf("cd: usage: cd [-L|-P] [dir]\n");
		ft_strclr(mode);
		return (NULL);
	}
//	Make sure the last option parsed have the priority
	i = -1;
	while (parsed_options && parsed_options[++i])
		mode[0] = parsed_options[i][0];
	i = 0;
//	Determine the return value
	while (args && args[++i])
		if (args[i][0])
			return (args[i]);
	return (NULL);
}

int		msh_handle_cd(char **args, char **env)
{
	char	*target;
	char	*home;
	char	*directory;
	char	*mode;


	home = msh_getenv("HOME", env);

	ft_printf("Home is '%s'\n", home);
	mode = ft_strdup("L");
	directory = msh_parse_cd(args, mode);
	ft_printf("The argument to be processed is '%s'\n", directory);
	ft_printf("The option is '%s'\n", mode);
	target = NULL;
	if (!directory)
		target = ft_strdup(home);
	else if (ft_strchr(directory, '~'))
		target = ft_find_and_replace(directory, "~", 0, home);
	else
		target = ft_strdup(directory);
	ft_printf("calling chdir on %s\n", target);
	
	if (chdir(target))
		ft_printf("cd: no such file or directory: '%s'\n", target);
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
