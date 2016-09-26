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

int		msh_handle_cd(char **args, char **env)
{
	char	*buf;
	char	*home;
	(void)env;

	home = msh_getenv("HOME", env);
	ft_printf("Home is '%s'\n", home);


	int	i;
	char	*hay;
	char	*needle;

	hay = ft_strdup("gsrejdekdjfgjdedf;kgjskde");
	needle = ft_strdup("de");
	i = ft_strstrcnt(hay, needle);
	ft_printf("There are %d instances of '%s' within '%s'\n", i, needle, hay);

	buf = ft_find_and_replace(hay, needle, 0, "iiiiiiiiiiiiii");
	ft_printf("%s\n", buf);
	if (ft_strchr(args[1], '~'))
		// Remplacer ~ par le home
	buf = getcwd(NULL, 0);
	//ft_printf("cwd is '%s'\n", buf);
	
	if (chdir(args[1]))
		ft_printf("chdir error with arg '%s'\n", args[1]);
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
