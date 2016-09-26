/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 18:29:07 by amulin            #+#    #+#             */
/*   Updated: 2016/09/26 16:37:32 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_getcwd(t_msh_vars *v)
{
	if (v->cwd)
		ft_strdel(&(v->cwd));
	v->cwd = getcwd(NULL, 0);
	if (!(v->cwd))
	{
		msh_error_exit("Error on getcwd()\n", errno);
	}
	return (0);
}

int	msh_exec_cwd(char *file, char **argv, t_msh_vars *v)
{
	int	ret;

	ret = -1;
	if (file[0] == '.' && file[1] == '/')
	{
		msh_getcwd(v);
		file = ft_strjoin(v->cwd, &file[1]);
		ret = execve(file, argv, v->environ);
	}
	else if (file[0] == '/')
		ret = execve(file, argv, v->environ);
	return (ret);
}

/*
**	Target flow:
**	- if command has 1 or more '/' in it, try to run it without path
**	- else try to run the command appended to each paths
*/
int	msh_exec(char *file, char **argv, t_msh_vars *v)
{
	char	*path;
	char	**dir;
	int		ret;
	int		i;

	if (ft_strchr(file, '/'))
		msh_exec_cwd(file, argv, v);
	
	file = ft_strjoin("/", file);
	path = msh_getenv("PATH", v->environ);
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
		ret = execve(path, argv, v->environ);
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
