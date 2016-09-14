#include "libft.h"
#include "libft_extra.h"
#include <sys/wait.h> // for linux


/*
 *	Multiprocess-compatible string color management, writing to stdout
 *	Recommend using ANSI color codes as defined in libft_extra.h
*/

int		ft_putstr_color_each(char *str, char *color)
{
	int		i;
	char	*out;

	out = ft_strnew(10);
	i = 0;
	if (ft_strlen(color) != 5)
		return (-1);
	while (str[i])
	{
		ft_strcat(out, color);
		ft_strncat(out, &str[i], 1);
		ft_strcat(out, ANSI_RESET);
		ft_putstr(out);
		ft_strclr(out);
		i++;
	}
	ft_strdel(&out);
	return (i);
}

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
	
	dir = ft_strsplit(path, ':'); // TODO : bugfix si \: dans un path

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
	int		pid_ret;

	statloc = 0;
	options = 0;


	line = ft_strnew(10);

	ns_print_prompt();
	while (get_next_line(STDIN_FILENO, &line))
	{
		args = ns_parse_line(line);
		pid_ret = fork();
		if (!pid_ret)
		{
			ft_putstr_color_each("This is child process\n", ANSI_FG_BLUE);
			ft_putstr_color_each("child about to exec...\n", ANSI_FG_BLUE);
			sleep(1);
			ft_putstr_color_each("child exec now\n", ANSI_FG_BLUE);
			ns_path_loop_exec(args[0], args, NULL);
		}
		else if (pid_ret != -1)
		{
			ft_putstr_color_each("This is parent process\n", ANSI_FG_YELLOW);
			ft_putstr_color_each("parent process waiting...\n", ANSI_FG_YELLOW);
			waitpid(-1, &statloc, options);
			ft_putstr_color_each("Child process over\n", ANSI_FG_YELLOW);
		}
		else
		{
			ft_printf("fork() error, exiting\n");
			exit(-1);
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
