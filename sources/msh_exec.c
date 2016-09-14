#include "minishell.h"

int	msh_path_loop_exec(char *file, char **argv, char **envp)
{
	char	*path;
	char	**dir;
	int		ret;
	int		i;

	file = ft_strjoin("/", file);

	path = msh_getenv("PATH");
	if (MSH_DEBUG_MODE)
	{
		ft_printf("file = '%s'\n", file);
		ft_printf("path = '%s'\n", path);
	}
	dir = ft_strsplit(path, ':'); // TODO : bugfix si \: dans un path

	ret = -1;
	i = 0;
	while (dir[i])
	{
		path = ft_strjoin(dir[i], file);
		if (MSH_DEBUG_MODE)
			ft_printf("trying on \033[32m%s\033[0m\n", path);
		ret = execve(path, argv, envp);
		if (MSH_DEBUG_MODE)
			ft_printf("execve returned %d\n", ret);
		ft_strdel(&path);
		i++;
	}
//	ft_printf("strerror(): %s\n", strerror(errno));
	ft_printf("%s: command not found: %s\n", PROG_NAME, &file[1]);
	exit(EX_ILLEG);
	return (0);
}
