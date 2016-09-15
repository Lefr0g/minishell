#include "minishell.h"

int		msh_init_vars(t_msh_vars *v)
{
	extern char	**environ;

	v->environ = ft_strarray_dup(environ);
	v->locales = (char**)malloc(sizeof(char*));
	ft_bzero(&(v->locales[0]), 1);
	return (0);
}

int		main(int ac, char **av)
{
	t_msh_vars	v;

	msh_init_vars(&v);
	(void)v;
	(void)av;
	/*
	i = -1;
	while (environ[++i])
		ft_printf("%s\n", environ[i]);
	*/

	if (ac != 1)
		ft_putstr("Invalid argument. This program doesn't take any.\n");
	else
	{
		msh_main_loop(&v);
	}
	return (0);
}
