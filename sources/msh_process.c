#include "minishell.h"

/*
 *	Main command interpretation function
 *	- Get stdin line
 *	- Parse line
 *	- Search file on path and execute
 *	- Repeat
*/
int		msh_main_loop(void)
{
	char	*line;
	char	**args;
//	int		i;
	int		statloc;
	int		options;
	int		pid_ret;

	statloc = 0;
	options = 0;
	line = ft_strnew(10);
	msh_print_prompt();
	while ((get_next_line(STDIN_FILENO, &line)!= -1))
	{
		args = msh_parse_line(line);
		pid_ret = fork();
		if (!pid_ret && ft_strlen(args[0]))
		{
			msh_debug_print_color("This is child process\n", ANSI_FG_BLUE);
			msh_debug_print_color("child about to exec...\n", ANSI_FG_BLUE);
		//	sleep(1);
			msh_debug_print_color("child exec now\n", ANSI_FG_BLUE);
			msh_path_loop_exec(args[0], args, NULL);
		}
		else if (pid_ret != -1)
		{
			msh_debug_print_color("This is parent process\n", ANSI_FG_YELLOW);
			msh_debug_print_color("parent process waiting...\n", ANSI_FG_YELLOW);
			waitpid(-1, &statloc, options);
			msh_debug_print_color("Child process over\n", ANSI_FG_YELLOW);
		}
		else
		{
			ft_printf("fork() error, exiting\n");
			exit(-1);
		}
		ft_strarray_del(&args);
		msh_print_prompt();
	}
	return (0);
}
