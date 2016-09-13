#include "libft.h"
#include "libft_extra.h"

int		ns_print_prompt(void)
{
	ft_putstr("$> ");
	return (0);
}

int	ns_path_loop_exec(char *file, char **argv,
		char **envp)
{
	char	*path;
	char	**dir;
	int		ret;
	int		i;

	path = ft_strdup(file);
	file = ft_strjoin("/", file);
//	ft_strdel(&path);

	path = getenv("PATH");
	ft_printf("file = '%s'\n", file);
	ft_printf("path = '%s'\n", path);
	
	dir = ft_strsplit(path, ':');

	ret = -1;
	i = 0;
	while (dir[i])
	{
		path = ft_strjoin(dir[i], file);
		ft_printf("trying on \033[32m%s\033[0m\n", path);
		ret = execve(path, argv, envp);
	//	ret = execve("/bin/ls", argv, envp);
		ft_printf("execve returned %d\n", ret);
		ft_strdel(&path);
		i++;
	}
	return (0);
}

void	ns_normalize_blanks(char *c)
{
	if (*c == '\t')
		*c = ' ';
}

/*
 *	This function takes one command line from stdin, replaces tabs with
 *	spaces, then splits the line into an array of strings using
 *	spaces as separator.
*/
char	**ns_parse_line(char *line)
{
	char	**tab;

	ft_striter(line, &ns_normalize_blanks);

	ft_printf("ns_parse_line, normalized line = '%s'\n", line);

	tab = ft_strsplit(line, ' ');
//*
	int		i;
	i = 0;
	while (tab && tab[i])
	{
		ft_printf("tab[%d] = %s\n", i, tab[i]);
		i++;
	}
//*/
	return (tab);
}

/*
 *	Main command interpretation function
 *	- Get stdin line
 *	- Parse line
 *	- Search file on path and execute
 *	- Repeat
*/
int		ns_main_loop(void)
{
	char	*line;
	char	**args;
	int		i;
	int		statloc;
	int		options;

	statloc = 0;
	options = 0;


	line = ft_strnew(10);

	ns_print_prompt();
	while (get_next_line(STDIN_FILENO, &line))
	{
		args = ns_parse_line(line);
		if (!fork())
		{
			ft_printf("\033[34mThis is child process\033[0m\n");
			ft_printf("\033[34mchild about to exec...\033[0m\n");
			sleep(1);
			ft_printf("\033[34mchild exec now\033[0m\n");
			ns_path_loop_exec(args[0], args, NULL);
		}
		else
		{
			ft_printf("\033[33mThis is parent process\033[0m\n");
			ft_printf("\033[33mparent process waiting...\033[0m\n");
			waitpid(-1, &statloc, options);
			ft_printf("\033[33mChild process over\033[0m\n");
		}
		ns_print_prompt();
	}
	return (0);
}

int		main(int ac, char **av)
{
	int			i;
	int			sub_ac;
	char		**sub_av;
	extern char	**environ;

	/*
	i = -1;
	while (environ[++i])
		ft_printf("%s\n", environ[i]);
	*/

	if (ac != 1)
		ft_putstr("Invalid argument. This program doesn't take any.\n");
	else
	{
		ns_main_loop();
	}
	return (0);
}
