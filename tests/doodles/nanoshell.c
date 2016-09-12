#include "libft.h"
#include "libft_extra.h"

char	*concatenate_args(int ac, char **av)
{
	int		i;
	int		len;
	char	*result;
	char	*buf;

	i = 0;
	len = 0;
	while (++i < ac)
		len += ft_strlen(av[i]);
	buf = ft_strnew(len + 1);
	i = 0;
	while (++i < ac)
	{
		ft_strcat(buf, av[i]);
		ft_strcat(buf, " ");
	}
	result = ft_strtrim(buf);
	ft_strdel(&buf);
	return (result);
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
	//	ret = execve(file, argv, envp);
		ret = execve("/bin/ls", argv, envp);
		ft_printf("execve returned %d\n", ret);
		ft_strdel(&path);
		i++;
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

	if (ac == 1)
		ft_putstr("please enter an argument\n");
	else
	{
		ft_printf("ac = %d\n", ac);
		sub_ac = ac - 1;

		if (!(sub_av = ft_strarray_dup(av)))
			return (-5);

		i = 0;
		while (i <= ac)
		{
		//	sub_av[i] = av[i + 1];
			ft_printf("sub_av[%d] = '%s'\n", i, sub_av[i]);
			i++;
		}
//		sub_av[i] = NULL;

		ft_printf("Executing command '%s' given as parameter :\n", av[1]);

		// TODO: recherche et essais successifs dans le PATH
		errno = 0;
		ft_strdel(&sub_av[0]);

		ns_path_loop_exec(sub_av[1], &sub_av[1], environ);


		if (errno)
			ft_printf("\033[31m////// Errno %d : %s\033[0m\n",
					errno, strerror(errno));
		ft_printf("Execution completed\n");
/*
		strbuf = concatenate_args(ac, av);
		if (strbuf)
			ft_printf("arguments : \"%s\"\n", strbuf);
*/
	}
//	ft_strdel(&strbuf);
	return (0);
}
