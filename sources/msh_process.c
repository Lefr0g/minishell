/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 18:29:25 by amulin            #+#    #+#             */
/*   Updated: 2016/09/26 17:10:38 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Fork the current process, and try to execute command on child process.
**	If the command is invalid, the msh_exec() function will exit on its own.
**	If an error occured during fork, an error message is printed theb minishell
**	exits.
**	The parent process waits for the child process completion before continuing
*/

void	msh_fork(char **args, t_msh_vars *v)
{
	int		pid_ret;
	int		statloc;
	int		options;

	statloc = 0;
	options = 0;
	pid_ret = fork();
	if (!pid_ret && ft_strlen(args[0]))
	{
		msh_debug_print_color("This is child process\n", ANSI_FG_BLUE);
		msh_debug_print_color("child exec now\n", ANSI_FG_BLUE);
		msh_exec(args[0], args, v);
	}
	else if (pid_ret != -1)
	{
		msh_debug_print_color("This is parent process\n", ANSI_FG_YELLOW);
		waitpid(-1, &statloc, options);
		msh_debug_print_color("Child process over\n", ANSI_FG_YELLOW);
	}
	else
	{
		ft_printf("fork() error, exiting\n");
		exit(-1);
	}
}

/*
 *	Main command interpretation function
 *	- Get stdin line
 *	- Parse line
 *	- Search file on path and execute
 *	- Repeat
*/

int		msh_main_loop(t_msh_vars *v, t_builtin_handler **builtin_func)
{
	char	*line;
	char	*buf;
	char	***cmds;
	int		i;

	line = ft_strnew(10);
	cmds = NULL;
	while (!msh_print_prompt() && (get_next_line(STDIN_FILENO, &line)!= -1))
	{
		cmds = msh_parse_line(line);
		i = 0;
		while (cmds && cmds[i])
		{
			if (cmds[i][0] && (buf = msh_is_builtin(cmds[i][0], v->builtin_name)))
				msh_handle_builtin(cmds[i], v, builtin_func);
			else if (cmds[i][0])
				msh_fork(cmds[i], v);
			i++;
		}
		if (cmds)
		{
			ft_strarray_del(cmds);
			free(cmds);
		}
	}
	return (0);
}
